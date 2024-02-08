#include "Set.h"
#include "../../../java/java.h"
jobjectArray Set::toArray()
{
	return (jobjectArray)Java::Env->CallObjectMethod(this->getInstance(), StrayCache::set_toArray);
}
