#include "java.h"
#include "../base.h"
#include "../sdk/JNIHelper.h"
#include "../util/logger.h"

jobject classLoader{};
jmethodID mid_findClass{};
void Java::SetUpBlcClassLoader() {
	jclass c_Thread = Java::GetInstance()->Env->FindClass("java/lang/Thread");
	jclass c_Map = Java::GetInstance()->Env->FindClass("java/util/Map");
	jclass c_Set = Java::GetInstance()->Env->FindClass("java/util/Set");
	jclass c_ClassLoader = Java::GetInstance()->Env->FindClass("java/lang/ClassLoader");

	jmethodID mid_getAllStackTraces = Java::GetInstance()->Env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
	jmethodID mid_keySet = Java::GetInstance()->Env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
	jmethodID mid_toArray = Java::GetInstance()->Env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
	jmethodID mid_getContextClassLoader = Java::GetInstance()->Env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
	mid_findClass = Java::GetInstance()->Env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
	jmethodID mid_currentThread = Java::GetInstance()->Env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

	jobject obj_stackTracesMap = Java::GetInstance()->Env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
	jobject obj_threadsSet = Java::GetInstance()->Env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

	jobjectArray threads = (jobjectArray)Java::GetInstance()->Env->CallObjectMethod(obj_threadsSet, mid_toArray);
	jint szThreads = Java::GetInstance()->Env->GetArrayLength(threads);

	for (int i = 0; i < szThreads; i++)
	{
		jobject thread = Java::GetInstance()->Env->GetObjectArrayElement(threads, i);
		jobject classLoaderObj = Java::GetInstance()->Env->CallObjectMethod(thread, mid_getContextClassLoader);

		if (classLoaderObj) {

			jstring className = Java::GetInstance()->Env->NewStringUTF("ave");
			jobject minecraftClass = Java::GetInstance()->Env->CallObjectMethod(classLoaderObj, mid_findClass, className);

			if (minecraftClass)
			{
				classLoader = classLoaderObj;

				Java::GetInstance()->Env->DeleteLocalRef(minecraftClass);

				break;
			}
		}

		Java::GetInstance()->Env->DeleteLocalRef(thread);
	}

	Java::GetInstance()->Env->DeleteLocalRef(threads);
	Java::GetInstance()->Env->DeleteLocalRef(obj_stackTracesMap);
	Java::GetInstance()->Env->DeleteLocalRef(obj_threadsSet);
	Java::GetInstance()->Env->DeleteLocalRef(c_Thread);
	Java::GetInstance()->Env->DeleteLocalRef(c_Map);
	Java::GetInstance()->Env->DeleteLocalRef(c_Set);
	Java::GetInstance()->Env->DeleteLocalRef(c_ClassLoader);

}

static void setupClassLoader()
{
	//Client Thread
	if (!JNIHelper::IsForge() && !JNIHelper::IsVanilla())
	{
		jclass c_Thread = Java::GetInstance()->Env->FindClass("java/lang/Thread");
		jclass c_Map = Java::GetInstance()->Env->FindClass("java/util/Map");
		jclass c_Set = Java::GetInstance()->Env->FindClass("java/util/Set");
		jclass c_ClassLoader = Java::GetInstance()->Env->FindClass("java/lang/ClassLoader");

		jmethodID mid_getAllStackTraces = Java::GetInstance()->Env->GetStaticMethodID(c_Thread, "getAllStackTraces", "()Ljava/util/Map;");
		jmethodID mid_keySet = Java::GetInstance()->Env->GetMethodID(c_Map, "keySet", "()Ljava/util/Set;");
		jmethodID mid_toArray = Java::GetInstance()->Env->GetMethodID(c_Set, "toArray", "()[Ljava/lang/Object;");
		jmethodID mid_getContextClassLoader = Java::GetInstance()->Env->GetMethodID(c_Thread, "getContextClassLoader", "()Ljava/lang/ClassLoader;");
		mid_findClass = Java::GetInstance()->Env->GetMethodID(c_ClassLoader, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		jmethodID mid_currentThread = Java::GetInstance()->Env->GetStaticMethodID(c_Thread, "currentThread", "()Ljava/lang/Thread;");

		jobject obj_stackTracesMap = Java::GetInstance()->Env->CallStaticObjectMethod(c_Thread, mid_getAllStackTraces);
		jobject obj_threadsSet = Java::GetInstance()->Env->CallObjectMethod(obj_stackTracesMap, mid_keySet);

		jobjectArray threads = (jobjectArray)Java::GetInstance()->Env->CallObjectMethod(obj_threadsSet, mid_toArray);
		jint szThreads = Java::GetInstance()->Env->GetArrayLength(threads);

		for (int i = 0; i < szThreads; i++)
		{
			jobject thread = Java::GetInstance()->Env->GetObjectArrayElement(threads, i);
			jobject classLoaderObj = Java::GetInstance()->Env->CallObjectMethod(thread, mid_getContextClassLoader);

			if (classLoaderObj) {

				jstring className = Java::GetInstance()->Env->NewStringUTF("net.minecraft.client.Minecraft");
				jobject minecraftClass = Java::GetInstance()->Env->CallObjectMethod(classLoaderObj, mid_findClass, className);

				if (minecraftClass)
				{
					classLoader = Java::GetInstance()->Env->NewGlobalRef(classLoaderObj);


					Java::GetInstance()->Env->DeleteLocalRef(minecraftClass);
					Java::GetInstance()->Env->DeleteLocalRef(classLoaderObj);

					break;
				}
			}

			Java::GetInstance()->Env->DeleteLocalRef(thread);
		}

		Java::GetInstance()->Env->DeleteLocalRef(threads);
		Java::GetInstance()->Env->DeleteLocalRef(obj_stackTracesMap);
		Java::GetInstance()->Env->DeleteLocalRef(obj_threadsSet);
		Java::GetInstance()->Env->DeleteLocalRef(c_Thread);
		Java::GetInstance()->Env->DeleteLocalRef(c_Map);
		Java::GetInstance()->Env->DeleteLocalRef(c_Set);
		Java::GetInstance()->Env->DeleteLocalRef(c_ClassLoader);
	}

}

void Java::InitFromEnv(JNIEnv* env) {;
	env->GetJavaVM(&Java::jvm);
	jint res = Java::jvm->GetEnv((void**)&Java::Jvmti, JVMTI_VERSION_1_2);
	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThreadAsDaemon((void**)&env, nullptr); //守护线程
	if (res != JNI_OK)
		std::cout << "Cant Setup Enviornment" << std::endl;



	this->Initialized = true; 
}

void Java::Init()
{
	if (this->Initialized) return;

	// Check if there is any Java VMs in the injected thread
	jsize count{};
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &count) != JNI_OK || count == 0)
		return;


	jint res = jvm->GetEnv((void**)&this->Env, JNI_VERSION_1_8);

	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThreadAsDaemon((void**)&this->Env, nullptr); //守护线程

	if (res != JNI_OK)
		return;

	jvm->GetEnv((void**)&Java::Jvmti, JVMTI_VERSION_1_2);
	if (this->Env == nullptr) {
		jvm->DetachCurrentThread();
		jvm->DestroyJavaVM();
	}
	
	Logger::Init();
	if (!classLoader)
	{
		setupClassLoader();
	}

	//JavaMap.insert(std::make_pair(GetCurrentThreadId(), this));


	this->Initialized = true;
}

void Java::Kill()
{
	jvm->DetachCurrentThread();
}

bool Java::AssignClass(std::string name, jclass& out)
{

	if (Base::version == BADLION or Base::version == FORGE_1_18_1)
	{
		jclass* loaded_classes = nullptr;
		jint loaded_classes_count = 0;
		jclass found_class = nullptr;
		jobject minecraft_classloader = nullptr;
		jvmtiEnv* tienv = Java::Jvmti;
		tienv->GetLoadedClasses(&loaded_classes_count, &loaded_classes);
		for (jint i = 0; i < loaded_classes_count; ++i)
		{
			char* signature_buffer = nullptr;
			tienv->GetClassSignature(loaded_classes[i], &signature_buffer, nullptr);
			std::string signature = signature_buffer;
			tienv->Deallocate((unsigned char*)signature_buffer);
			signature = signature.substr(1);
			signature.pop_back();
			size_t pos = signature.find("/");
			while (pos != std::string::npos) {
				signature.replace(pos, 1, ".");
				pos = signature.find("/", pos + 1);
			}
			//std::cout << signature << std::endl;
			if (signature == name)
			{
				out = (jclass)Java::GetInstance()->Env->NewLocalRef(loaded_classes[i]);
				break;
			}
		}
		for (jint i = 0; i < loaded_classes_count; ++i)
		{
			Java::GetInstance()->Env->DeleteLocalRef(loaded_classes[i]);
		}
		tienv->Deallocate((unsigned char*)loaded_classes);
		return true;
	}

	if (JNIHelper::IsForge()) {
		out = JNIHelper::ForgeFindClass(name.c_str());
		return true;
	}

	if (JNIHelper::IsVanilla()) {
		out = Java::GetInstance()->Env->FindClass(name.c_str());
		return true;
	}

	jstring className = Java::GetInstance()->Env->NewStringUTF(name.c_str());
	jobject findClass = Java::GetInstance()->Env->CallObjectMethod(classLoader, mid_findClass, className);

	if (findClass)
	{
		out = (jclass)findClass;
		return true;
	}

	return false;
}
