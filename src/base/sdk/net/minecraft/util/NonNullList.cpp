#include "NonNullList.h"

List CNonNullList::getList(JNIEnv* env )
{
	return List(env->GetObjectField(this->instance, StrayCache::nonNullList_List));
}
