#pragma once

#include <string>

#include "../../../ext/jni/jni.h"
#include "../../../ext/jni/jvmti.h"

struct Java
{
	static void InitFromEnv(JNIEnv* env);
	static void Init();
	static void SetUpBlcClassLoader();
	static void Kill();

	static bool AssignClass(std::string name, jclass& out);
	static inline JNIEnv* Env;
	static inline jvmtiEnv* Jvmti;
	static inline JavaVM* jvm;
	static inline bool Initialized;
};

