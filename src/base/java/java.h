#pragma once

#include <string>

#include "../../../ext/jni/jni.h"
#include "../../../ext/jni/jvmti.h"

#include <map>

#include <memory>

#include <Windows.h>
#include "../Base.h"

class Java;
std::map<DWORD, std::shared_ptr<Java>> JavaMap;

class Java
{
public:

	~Java() {
	}

	static Java* GetInstance()
	{

		auto threadID = GetCurrentThreadId();
		if (auto it = JavaMap.find(threadID);it != JavaMap.end())
		{
			return it->second.get();
		}
		auto shared = std::make_shared<Java>();
		JavaMap[threadID] = shared;
		return shared.get();
	}
	void InitFromEnv(JNIEnv* env);
	void Init();
	void SetUpBlcClassLoader();
	static void Kill();

	bool AssignClass(std::string name, jclass& out);
	JNIEnv* Env;
	static inline jvmtiEnv* Jvmti;
	static inline JavaVM* jvm;
	bool Initialized;
};

#define JavaInstance Java::GetInstance()