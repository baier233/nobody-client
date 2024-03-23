#include "item.h"

#include "../../../strayCache.h"

int CItem::GetIdFromItem(CItem item, JNIEnv* env)
{
	return env->CallStaticIntMethod(this->getClass(), StrayCache::GetInstance()->item_getIdFromItem, item.getInstance());

}
