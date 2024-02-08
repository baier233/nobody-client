#include "ItemArmor.h"

#include "../../../strayCache.h"


//CItemArmor::CItemArmor()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::itemArmor_Class;
//}
//
//CItemArmor::CItemArmor(jobject instance) : CItemArmor()
//{
//	this->Instance = instance;
//}
//
//jclass CItemArmor::getClass()
//{
//	return this->Class;
//}
//
//jobject CItemArmor::getInstance()
//{
//	return this->Instance;
//}
//
CItemArmor::CItemArmor(CItem item) {
	this->instance = Java::Env->NewGlobalRef(item.getInstance());
}
int CItemArmor::getColor(CItemStack stack) {
	if (!stack.check()) return NULL;
	if (!stack.GetItem().getInstance()) return NULL;
	if (!Java::Env->IsInstanceOf(stack.GetItem().getInstance(),StrayCache::itemArmor_Class)) return NULL;


	return Java::Env->CallIntMethod(this->getInstance(), StrayCache::itemArmor_getColor , stack.getInstance());
}