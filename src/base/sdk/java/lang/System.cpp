#include "System.h"

void System::gc(JNIEnv* env)
{
	env->CallStaticVoidMethod(StrayCache::system_class, StrayCache::system_gc);
}
