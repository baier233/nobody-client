#include "String.h"
#include "../../../java/java.h"


String::String(std::string text)
{
	this->instance = (jobject)Java::Env->NewStringUTF(text.c_str());
}


std::string String::ToString()
{
	jstring jStr = (jstring)this->getInstance();
	const char* nativeStr = Java::Env->GetStringUTFChars(jStr, nullptr);
	Java::Env->ReleaseStringUTFChars(jStr, nativeStr);
	return std::string(nativeStr);
}

bool String::contains(jstring str) {
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::string_contains, str);
}

