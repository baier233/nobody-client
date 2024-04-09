#include "System.h"

void System::gc(JNIEnv* env)
{
	env->CallStaticVoidMethod(StrayCache::GetInstance()->system_class, StrayCache::GetInstance()->system_gc);
}
