#pragma once
#include "../JVM.hpp"
#include "../../../../ext/jni/jni.h"
#include "../../java/java.h"
namespace JavaHook
{
	//        |-------------------------------------------------------|

	//        | c_rarg0   c_rarg1  c_rarg2 c_rarg3 c_rarg4 c_rarg5    |

	//        |-------------------------------------------------------|

	//        | rcx       rdx      r8      r9      rdi*    rsi*       | windows (* not a c_rarg)

	//        | rdi       rsi      rdx     rcx     r8      r9         | solaris/linux

	//        |-------------------------------------------------------|

	//        | j_rarg5   j_rarg0  j_rarg1 j_rarg2 j_rarg3 j_rarg4    |

	//        |-------------------------------------------------------|
	typedef void(*callback_t)(void* sp, bool* should_return, void* rbx, void* thread);

	void clean();
	void partial_clean();
	bool init();

	void add_to_java_hook(jmethodID methodID, callback_t interpreted_callback, jclass owner = nullptr);

	jobject oop_to_jobject(void* oop, void* thread);
	jobject oop_to_jobject(void* oop, JNIEnv* env);
	template<typename T> inline void set_primitive_return_value(bool* should_return, T value)
	{
		*(T*)((uint64_t*)should_return + 8) = value;
	}

	//args right to left (including this pointer)
	template<typename T> inline T get_primitive_arg_at(void* sp, int index)
	{
		return *(T*)((uint64_t*)sp + 1 + index);
	}
	jobject get_jobject_arg_at(void* sp, int index, void* thread, JNIEnv* env = Java::Env);

	JNIEnv* get_env_for_thread(void* thread);
	JNIEnv* get_current_thread_env();

	inline bool is_old_java = false;
}
struct HookedJavaMethodCache
{
	JavaHook::callback_t interpreted_callback;
	uint8_t* prev_i2i_entry = nullptr;
	uint8_t* original_i2i_entry = nullptr;
};
