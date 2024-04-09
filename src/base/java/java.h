#pragma once

#include <string>

#include "../../../ext/jni/jni.h"
#include "../../../ext/jni/jvmti.h"

#include <map>

#include <memory>

#include <Windows.h>
#include "../Base.h"

class Java
{
public:

	~Java() {
		for (auto &pair : ContextMap)
		{
			if (pair.second->currentJava == this)
			{
				pair.second->currentJava = nullptr;
				break;
			}
		}
	}

	static Java* GetInstance()
	{
		auto thread = GetCurrentThreadId() ;
		if (ContextMap.find(thread) != ContextMap.end() && ContextMap[thread]->currentJava)
		{
			return ContextMap[thread]->currentJava;
		}

		Java instance;

	

		if (auto ctx = ContextMap[thread];ctx)
		{
			ctx->currentJava = &instance;
			return &instance;
		}

		auto threadCtx = new ThreadContext();
		threadCtx->currentJava = &instance;
		ContextMap[thread] = threadCtx;
		return &instance;
	}
	void InitFromEnv(JNIEnv* env);
	void Init();
	void SetUpBlcClassLoader();
	void Kill();

	bool AssignClass(std::string name, jclass& out);
	JNIEnv* Env;
	static inline jvmtiEnv* Jvmti;
	static inline JavaVM* jvm;
	bool Initialized;
};