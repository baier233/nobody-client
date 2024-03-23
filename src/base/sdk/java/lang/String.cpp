#include "String.h"
#include "../../../java/java.h"


String::String(std::string text, JNIEnv* env)
{
	this->instance = (jobject)env->NewStringUTF(text.c_str());
}


std::string String::ToString(JNIEnv* env)
{
	jstring jStr = (jstring)this->getInstance();
	const char* nativeStr = env->GetStringUTFChars(jStr, nullptr);
	env->ReleaseStringUTFChars(jStr, nativeStr);
	return std::string(nativeStr);
}

bool String::contains(jstring str, JNIEnv* env) {
	return env->CallBooleanMethod(this->getInstance(), StrayCache::GetInstance()->string_contains, str);
}

