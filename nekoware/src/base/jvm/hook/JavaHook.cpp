#include "JavaHook.h"
#include <Windows.h>
#include "../../util/module/Module.hpp"
#include "../../../../ext/jni/jvmti.h"

static uint8_t* generate_detour_code(JavaHook::callback_t callback, uint8_t* original_addr);
static jobject(*make_local)(void* thread, void* oop, int alloc_failure) = nullptr;
static jobject(*make_local2)(JNIEnv* env, void* oop) = nullptr;

static std::unordered_map<jmethodID, HookedJavaMethodCache> hookedMethods{};

void JavaHook::clean()
{

	for (const std::pair<jmethodID, HookedJavaMethodCache>& m : hookedMethods)
	{
		auto method = VMType::from_instance("Method", *(void**)m.first).value();
		uint8_t** p_i2i_entry = (uint8_t**)method.get_field<uint8_t*>("_i2i_entry").value();
		uint8_t** p_from_interpreted_entry = method.get_field<uint8_t*>("_from_interpreted_entry").value();
		if (m.second.original_i2i_entry)
		{
			*p_from_interpreted_entry = m.second.original_i2i_entry; //restore entries
			*p_i2i_entry = m.second.original_i2i_entry;
		}
		if (m.second.prev_i2i_entry)
			VirtualFree(m.second.prev_i2i_entry, 0, MEM_RELEASE);

		//unsigned short* _flags = (unsigned short*)(method + 0x32);
		//*_flags &= ~(1 << 2);

		jint* access_flags = method.get_field<jint>("_access_flags").value();
		//*access_flags &= ~0x01000000;
		*access_flags &= ~0x02000000;
		*access_flags &= ~0x04000000;
		*access_flags &= ~0x08000000;
	}
}

void JavaHook::partial_clean()
{
	for (const std::pair<jmethodID, HookedJavaMethodCache>& m : hookedMethods)
	{
		if (m.second.prev_i2i_entry)
			VirtualFree(m.second.prev_i2i_entry, 0, MEM_RELEASE);
	}
}


extern "C" JNIIMPORT VMStructEntry * gHotSpotVMStructs;
extern "C" JNIIMPORT VMTypeEntry * gHotSpotVMTypes;
bool JavaHook::init()
{
	VMTypes::init(gHotSpotVMStructs, gHotSpotVMTypes);
	Module jvmdll("jvm.dll");
	uint8_t make_local_pattern[] =
	{
		0x48, 0x85, 0xD2, 0x75, 0x03, 0x33, 0xC0, 0xC3,
		0x48, 0x8B, 0x89, 0xD8, 0x00, 0x00, 0x00, 0xE9,
		0x6C, 0xF7, 0xFF, 0xFF
	};

	make_local = (jobject(*)(void*, void*, int))
		jvmdll.pattern_scan(make_local_pattern, sizeof(make_local_pattern), PAGE_EXECUTE_READ);
	if (!make_local)
	{
		is_old_java = true;
		//try second pattern, for lower jvm versions
		uint8_t make_local_pattern2[] =
		{
			0x48, 0x85, 0xD2, 0x75, 0x03, 0x33, 0xC0, 0xC3, 0x48, 0x8B, 0x49
		};
		make_local = (jobject(*)(void*, void*, int))
			jvmdll.pattern_scan(make_local_pattern2, sizeof(make_local_pattern2), PAGE_EXECUTE_READ);
	}
	if (!make_local) {
		is_old_java = true;
		uint8_t make_local_pattern3[] =
		{
			0x48, 0x89, 0x5C, 0x24, 0x10, 0x48, 0x89, 0x6C,
			0x24, 0x18, 0x48, 0x89, 0x74, 0x24, 0x20, 0x57,
			0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B, 0xF2, 0x48,
			0x8B, 0xF9
		};
		make_local2 = (jobject(*)(JNIEnv*, void*))
			jvmdll.pattern_scan(make_local_pattern3, sizeof(make_local_pattern3), PAGE_EXECUTE_READ);
	}
	return true;
}
#include "./../../java/java.h"
#include <thread>

void JavaHook::add_to_java_hook(jmethodID methodID, callback_t interpreted_callback) {
	static int runonce = []()->int
		{
			jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
			Java::Jvmti->AddCapabilities(&capabilities);
			return 0;
		}();
		jclass owner{};
		Java::Jvmti->GetMethodDeclaringClass(methodID, &owner);
		Java::Jvmti->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
		Java::Env->DeleteLocalRef(owner);

		uint8_t* method = *((uint8_t**)methodID);
		HookedJavaMethodCache& m = hookedMethods[methodID];
		m.interpreted_callback = interpreted_callback;

		//unsigned short* _flags = (unsigned short*)(method + 0x32);
		//*_flags |= (1 << 2); //don't inline

		int* access_flags = (int*)(method + (is_old_java ? 0x20 : 0x28));
		//*access_flags |= 0x01000000; //fake onqueue
		*access_flags |= 0x02000000; //no compile
		*access_flags |= 0x04000000;
		*access_flags |= 0x08000000;

		uint8_t** p_i2i_entry = (uint8_t**)(method + (is_old_java ? 0x30 : 0x38));
		uint8_t* _i2i_entry = *p_i2i_entry;
		if (_i2i_entry && _i2i_entry != m.prev_i2i_entry)
		{
			//std::cout << "hooking" << '\n';
			uint8_t* new_i2i_entry = generate_detour_code(m.interpreted_callback, _i2i_entry);
			m.original_i2i_entry = _i2i_entry;
			*p_i2i_entry = new_i2i_entry;
			uint8_t** p_from_interpreted_entry = (uint8_t**)(method + 0x50);
			*p_from_interpreted_entry = *p_i2i_entry;
			uint8_t* _adapter = *(uint8_t**)(method + (is_old_java ? 0x38 : 0x20));
			uint8_t* _c2i_entry = *(uint8_t**)(_adapter + 0x20);
			uint8_t** p_from_compiled_entry = (uint8_t**)(method + 0x40);
			*p_from_compiled_entry = _c2i_entry;
			if (m.prev_i2i_entry)
				VirtualFree(m.prev_i2i_entry, 0, MEM_RELEASE);
			m.prev_i2i_entry = new_i2i_entry;
			//*((uint8_t**)(method + 0x48)) = nullptr; // delete compiled code
		}
		return;
}


//void JavaHook::add_to_java_hook(jmethodID methodID, callback_t interpreted_callback, jclass owner)
//{
//	static int runonce = []()->int
//		{
//			jvmtiCapabilities capabilities{ .can_retransform_classes = JVMTI_ENABLE };
//			Java::Jvmti->AddCapabilities(&capabilities);
//			return 0;
//		}();
//		if (!owner)
//		{
//			Java::Jvmti->GetMethodDeclaringClass(methodID, &owner);
//			Java::Jvmti->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
//			Java::Env->DeleteLocalRef(owner);
//		}
//		else {
//			Java::Jvmti->RetransformClasses(1, &owner); //small trick to delete any already compiled / inlined code
//		}
//
//
//		HookedJavaMethodCache& m = hookedMethods[methodID];
//		m.interpreted_callback = interpreted_callback;
//
//		auto method = VMType::from_instance("Method", *(void**)methodID).value();
//
//		jint* _access_flags = method.get_field<jint>("_access_flags").value();
//		*_access_flags |= 0x02000000; //no compile
//		*_access_flags |= 0x04000000;
//		*_access_flags |= 0x08000000;
//
//		uint8_t** p_i2i_entry = (uint8_t**)method.get_field<uint8_t*>("_i2i_entry").value();
//		uint8_t* _i2i_entry = *p_i2i_entry;
//
//		if (_i2i_entry && _i2i_entry != m.prev_i2i_entry)
//		{
//			uint8_t* new_i2i_entry = generate_detour_code(m.interpreted_callback, _i2i_entry);
//			m.original_i2i_entry = _i2i_entry;
//			*p_i2i_entry = new_i2i_entry;
//			uint8_t** p_from_interpreted_entry = method.get_field<uint8_t*>("_from_interpreted_entry").value();
//			*p_from_interpreted_entry = *p_i2i_entry;
//			uint8_t* _adapter = *method.get_field<uint8_t*>("_adapter").value();
//			uint8_t* _c2i_entry = *(uint8_t**)(_adapter + 0x20);
//			uint8_t** p_from_compiled_entry = method.get_field<uint8_t*>("_from_compiled_entry").value();
//			*p_from_compiled_entry = _c2i_entry;
//			if (m.prev_i2i_entry)
//				VirtualFree(m.prev_i2i_entry, 0, MEM_RELEASE);
//			m.prev_i2i_entry = new_i2i_entry;
//
//			//*((uint8_t**)(method + 0x48)) = nullptr; // delete compiled code
//		}
//}

jobject JavaHook::oop_to_jobject(void* oop, void* thread)
{
	return make_local(thread, oop, 0);
}

jobject JavaHook::oop_to_jobject(void* oop, JNIEnv* env)
{
	return make_local2(env, oop);
}

jobject JavaHook::get_jobject_arg_at(void* sp, int index, void* thread, JNIEnv* env)
{

	void* oop = get_primitive_arg_at<void*>(sp, index);
	if (!oop) return nullptr;
	if (JavaHook::is_old_java)
	{
		return oop_to_jobject(oop, env);
	}
	return oop_to_jobject(oop, thread);
}

JNIEnv* JavaHook::get_env_for_thread(void* thread)
{
	static uintptr_t offset = VMTypes::findTypeFields("JavaThread").value().get()["_anchor"]->offset + 0x20;
	return (JNIEnv*)((uintptr_t)thread + offset);
}

JNIEnv* JavaHook::get_current_thread_env()
{
	static std::unordered_map<std::thread::id, JNIEnv*> env_cache{};
	try
	{
		return env_cache.at(std::this_thread::get_id());
	}
	catch (...)
	{
		JNIEnv* env = nullptr;
		JavaVM* jvm = Java::jvm;
		if (!jvm)
			return nullptr;
		if (jvm->GetEnv((void**)&env, JNI_VERSION_1_8) == JNI_EDETACHED)
			jvm->AttachCurrentThreadAsDaemon((void**)&env, nullptr);
		if (env)
			env_cache.insert({ std::this_thread::get_id(), env });
		return env;
	}
	return nullptr;
}

uint8_t* AllocateNearbyMemory(uint8_t* nearby_addr, int size, int access = PAGE_EXECUTE_READWRITE)
{
	//this is slow, maybe change the value
	int fail = 0;
	for (int i = 65536;
		i < 0x7FFFFFFF;
		i += 65536)
	{
		uint8_t* allocated = (uint8_t*)VirtualAlloc(nearby_addr + i, size, MEM_COMMIT | MEM_RESERVE, access);
		if (allocated)
		{
			//std::cout << "fails: " << fail << std::endl;
			return allocated;
		}
		allocated = (uint8_t*)VirtualAlloc(nearby_addr - i, size, MEM_COMMIT | MEM_RESERVE, access);
		if (allocated)
		{
			//std::cout << "fails: " << fail << std::endl;
			return allocated;
		}
		fail++;
	}
	return nullptr;
}

uint8_t* generate_detour_code(JavaHook::callback_t callback, uint8_t* original_addr)
{
	/*
	   0:  50                      push   rax
	   1:  51                      push   rcx
	   2:  52                      push   rdx
	   3:  41 50                   push   r8
	   5:  41 51                   push   r9
	   7:  41 52                   push   r10
	   9:  41 53                   push   r11
	   b:  55                      push   rbp
	   c:  6a 00                   push   0x0
	   e:  48 89 e5                mov    rbp,rsp
	   11: 48 83 e4 f0             and    rsp,0xfffffffffffffff0
	   15: 48 8d 4d 48             lea    rcx,[rbp+0x48]
	   19: 48 89 ea                mov    rdx,rbp
	   1c: 49 89 d8                mov    r8,rbx
	   1f: 4d 89 f9                mov    r9,r15
	   22: 48 83 ec 20             sub    rsp,0x20
	   26: 48 b8 11 11 11 11 11    movabs rax,0x1111111111111111
	   2d: 11 11 11
	   30: ff d0                   call   rax
	   32: 48 89 ec                mov    rsp,rbp
	   35: 58                      pop    rax
	   36: 48 83 f8 00             cmp    rax,0x0
	   3a: 5d                      pop    rbp
	   3b: 41 5b                   pop    r11
	   3d: 41 5a                   pop    r10
	   3f: 41 59                   pop    r9
	   41: 41 58                   pop    r8
	   43: 5a                      pop    rdx
	   44: 59                      pop    rcx
	   45: 58                      pop    rax
	   46: 74 06                   je     0x4e
	   48: 5f                      pop    rdi
	   49: 4c 89 ec                mov    rsp,r13
	   4c: ff e7                   jmp    rdi
	   4e: e9 00 00 00 00          jmp    0x53
   */
	uint8_t assembly[] =
	{
		0x50, 0x51, 0x52, 0x41, 0x50, 0x41, 0x51, 0x41, 0x52, 0x41, 0x53, 0x55, 0x6A, 0x00,
		0x48, 0x89, 0xE5, 0x48, 0x83, 0xE4, 0xF0, 0x48, 0x8D, 0x4D, 0x48, 0x48, 0x89, 0xEA,
		0x49, 0x89, 0xD8, 0x4D, 0x89, 0xF9, 0x48, 0x83, 0xEC, 0x20, 0x48, 0xB8, 0x11, 0x11,
		0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xFF, 0xD0, 0x48, 0x89, 0xEC, 0x58, 0x48, 0x83,
		0xF8, 0x00, 0x5D, 0x41, 0x5B, 0x41, 0x5A, 0x41, 0x59, 0x41, 0x58, 0x5A, 0x59, 0x58,
		0x74, 0x06, 0x5F, 0x4C, 0x89, 0xEC, 0xFF, 0xE7, 0xE9, 0x00, 0x00, 0x00, 0x00
	};
	DWORD original_protection = 0;
	uint8_t* allocated_instructions = AllocateNearbyMemory(original_addr, sizeof(assembly));
	if (!allocated_instructions)
		return nullptr;

	memcpy(allocated_instructions, assembly, sizeof(assembly));

	*(void**)(allocated_instructions + 0x28) = callback;
	uint8_t* rip = allocated_instructions + 0x53;
	int32_t offset = original_addr - rip;
	*(int32_t*)(allocated_instructions + 0x4F) = offset;


	if (!VirtualProtect(allocated_instructions, sizeof(assembly), PAGE_EXECUTE_READ, &original_protection))
		return nullptr;

	return allocated_instructions;
}
