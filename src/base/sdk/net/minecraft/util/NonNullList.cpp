#include "NonNullList.h"

List CNonNullList::getList()
{
	return List(Java::Env->GetObjectField(this->instance,StrayCache::nonNullList_List));
}
