#include "List.h"
#include "../../../java/java.h"


jobjectArray List::toArray(JNIEnv* env)
{
	if (this->instance == nullptr)
	{
		return NULL;
	}

	return (jobjectArray)env->CallObjectMethod(this->instance, StrayCache::GetInstance()->list_toArray);
}
