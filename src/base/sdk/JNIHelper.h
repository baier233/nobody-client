#pragma once
#include "../../../ext/jni/jni.h"
#include "../java/java.h"

class JNIHelper
{
private:
	inline static jclass LaunchWrapperClassLoaderClass;
	inline static jmethodID FindClassMethodID;
	inline static jclass LaunchClass;
	inline static jfieldID ClassLoaderFieldID;
	inline static jobject ClassLoaderObject;

	static bool AlreadyCheckedForge;
	static bool IsForgeExisting;

public:
	inline static JNIEnv* env;
	static jclass ForgeFindClass(const char*);
	static bool IsForge();
	static bool IsVanilla();
	static std::string jstring2string(JNIEnv* env, jstring str);
	static std::string UtfToGbk(const char* utf8);
};