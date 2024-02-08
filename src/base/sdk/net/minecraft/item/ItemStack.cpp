#include "ItemStack.h"

//CItemStack::CItemStack()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::itemStack_class;
//}
//
//CItemStack::CItemStack(jobject instance) : CItemStack()
//{
//	this->Instance = instance;
//}
//
//jclass CItemStack::getClass()
//{
//	return this->Class;
//}
//
//jobject CItemStack::getInstance()
//{
//	return this->Instance;
//}

CItem CItemStack::GetItem()
{
	return CItem(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::itemStack_getItem));
}


float CItemStack::GetStrVsBlock(CBlock block)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	if (Base::version == 1)return 1.f;
	return Java::Env->CallFloatMethod(this->instance, StrayCache::itemStack_getStrVsBlock,block.getInstance());
}

float CItemStack::GetStrVsBlock(CIBlockState block)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	if (Base::version != 1)return 1.f;
	return Java::Env->CallFloatMethod(this->instance, StrayCache::itemStack_getStrVsBlock,block.getInstance());
}
