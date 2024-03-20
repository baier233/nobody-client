#pragma once
#include "include_header.h"
namespace JavaHook {
	namespace JVM {
		bool Init(JNIEnv* env);
	}
	class MethodHook {
		MethodHook();
		~MethodHook();
	public:
		void InitHook(const jmethodID method,const void* detour);

	private:
		java_hotspot::method* target_method;
		void* detour;
	};
}

