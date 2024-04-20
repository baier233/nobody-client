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

CItem CItemStack::GetItem(JNIEnv* env )
{
	return CItem(env->CallObjectMethod(this->getInstance(), StrayCache::itemStack_getItem));
}


float CItemStack::GetStrVsBlock(CBlock block, JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return NULL;
	if (Base::version == FORGE_1_12_2 || Base::version == LUNAR_1_12_2)return 1.f;
	return env->CallFloatMethod(this->instance, StrayCache::itemStack_getStrVsBlock, block.getInstance());
}

float CItemStack::GetStrVsBlock(CIBlockState block, JNIEnv* env )
{
	if (!this->isValid() || this->isNULL()) return NULL;
	if (Base::version != FORGE_1_12_2 && Base::version != LUNAR_1_12_2 && Base::version != FORGE_1_18_1)return 1.f;
	return env->CallFloatMethod(this->instance, StrayCache::itemStack_getStrVsBlock, block.getInstance());
}
