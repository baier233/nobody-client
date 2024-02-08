#include "List.h"
#include "../../../java/java.h"


jobjectArray List::toArray()
{
	if (this->instance == nullptr)
	{
		return NULL;
	}

	return (jobjectArray) Java::Env->CallObjectMethod(this->instance, StrayCache::list_toArray);
}
