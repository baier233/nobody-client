#include "System.h"

void System::gc()
{
	Java::Env->CallStaticVoidMethod(StrayCache::system_class, StrayCache::system_gc);
}
