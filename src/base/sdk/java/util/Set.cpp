#include "Set.h"
#include "../../../java/java.h"
jobjectArray Set::toArray(JNIEnv* env)
{
	return (jobjectArray)env->CallObjectMethod(this->getInstance(), StrayCache::set_toArray);
}
