#include "ItemArmor.h"

#include "../../../strayCache.h"


CItemArmor::CItemArmor(CItem item, JNIEnv* env) {
	this->instance = env->NewGlobalRef(item.getInstance());
}
int CItemArmor::getColor(CItemStack stack, JNIEnv* env) {
	if (!stack.check()) return NULL;
	if (!stack.GetItem().getInstance()) return NULL;
	if (Base::version == FORGE_1_18_1)
	{
		if (!env->IsInstanceOf(stack.getInstance(), StrayCache::dyeableLeatherItem_class)) return NULL;
		return env->CallIntMethod(this->instance, StrayCache::dyeableLeatherItem_getColor);
	}

	if (!env->IsInstanceOf(stack.GetItem().getInstance(), StrayCache::itemArmor_Class)) return NULL;
	

	return env->CallIntMethod(this->getInstance(), StrayCache::itemArmor_getColor, stack.getInstance());
}