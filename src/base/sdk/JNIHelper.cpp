#include "JNIHelper.h"
#include <Windows.h>
#include <iostream>

bool JNIHelper::AlreadyCheckedForge = false;
bool JNIHelper::IsForgeExisting = false;

jclass JNIHelper::ForgeFindClass(const char* name)
{
	if (LaunchWrapperClassLoaderClass == NULL)
	{
		LaunchWrapperClassLoaderClass = Java::Env->FindClass("net/minecraft/launchwrapper/LaunchClassLoader");
		if (LaunchWrapperClassLoaderClass == NULL) return NULL;
	}

	if (FindClassMethodID == NULL)
	{
		FindClassMethodID = Java::Env->GetMethodID(LaunchWrapperClassLoaderClass, "findClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		if (FindClassMethodID == NULL) return NULL;
	}

	if (LaunchClass == NULL)
	{
		LaunchClass = Java::Env->FindClass("net/minecraft/launchwrapper/Launch");
		if (LaunchClass == NULL) return NULL;
	}

	if (ClassLoaderFieldID == NULL)
	{
		ClassLoaderFieldID = Java::Env->GetStaticFieldID(LaunchClass, "classLoader", "Lnet/minecraft/launchwrapper/LaunchClassLoader;");
		if (ClassLoaderFieldID == NULL) return NULL;
	}

	if (ClassLoaderObject == NULL)
	{
		ClassLoaderObject = Java::Env->GetStaticObjectField(LaunchClass, ClassLoaderFieldID);
		if (ClassLoaderObject == NULL) return NULL;
	}

	jstring jname = Java::Env->NewStringUTF(name);
	jclass cls = (jclass)Java::Env->CallObjectMethod(ClassLoaderObject, FindClassMethodID, jname);

	Java::Env->DeleteLocalRef(jname);

	return cls;
}

bool JNIHelper::IsForge()
{
	if (!AlreadyCheckedForge)
	{
		AlreadyCheckedForge = true;
		jclass forgeClass = Java::Env->FindClass("net/minecraftforge/common/ForgeVersion");
		std::cout << forgeClass << std::endl;
		if (forgeClass != NULL)
		{
			Java::Env->DeleteLocalRef(forgeClass);
			IsForgeExisting = true;
		}
	}
	return IsForgeExisting;
}

bool JNIHelper::IsVanilla()
{
	if (!IsForge() && FindWindowA(NULL, "Minecraft 1.8.9")) {
		return true;
	}
	return false;
}

std::string JNIHelper::jstring2string(JNIEnv* env, jstring jStr)
{
	if (!jStr)
		return "";

	const jclass stringClass = env->GetObjectClass(jStr);
	const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
	const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

	size_t length = (size_t)env->GetArrayLength(stringJbytes);
	jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

	std::string ret = std::string((char*)pBytes, length);
	env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

	env->DeleteLocalRef(stringJbytes);
	env->DeleteLocalRef(stringClass);
	return ret;
}

std::string JNIHelper::UtfToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
