#include "item.h"

#include "../../../strayCache.h"

int CItem::GetIdFromItem(CItem item)
{
    return Java::Env->CallStaticIntMethod(this->getClass(), StrayCache::item_getIdFromItem, item.getInstance());

}
