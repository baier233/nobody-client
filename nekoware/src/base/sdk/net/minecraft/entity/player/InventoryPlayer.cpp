#include "InventoryPlayer.h"

#include "../../../../strayCache.h"
#include "../../../../java/util/List.h"
#include "../../util/NonNullList.h"
//CInventoryPlayer::CInventoryPlayer()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::inventoryPlayer_class;
//}
//
//CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
//{
//	this->Instance = instance;
//}
//
//jclass CInventoryPlayer::getClass()
//{
//	return this->Class;
//}
//
//jobject CInventoryPlayer::getInstance()
//{
//	return this->Instance;
//}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}

void CInventoryPlayer::SetCurrentItem(int index)
{
	Java::Env->SetIntField(this->getInstance(), StrayCache::inventoryPlayer_currentItem, index);
}

CItemStack CInventoryPlayer::GetIndexItem(int index)
{
	jobject mainInventory = Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_mainInv);
	jobject itemstack = Java::Env->GetObjectArrayElement((jobjectArray)mainInventory, index);
	return CItemStack(itemstack);

}
CItemStack CInventoryPlayer::GetStackInSlot(int index)
{
	return CItemStack(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::inventoryPlayer_getStackInSlot,index));

}

CItemStack CInventoryPlayer::GetArmorItem(int index)
{

	if (!isValid() || isNULL())
	{
		return CItemStack{};
	}
	jobjectArray array;
	if (Base::version == 1)
	{
		array = CNonNullList(Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_armorInv)).getList().toArray();
	} else {
		array = (jobjectArray)Java::Env->GetObjectField(this->getInstance(), StrayCache::inventoryPlayer_armorInv);
	}
	if (!array) return CItemStack();
	jobject itemstack = Java::Env->GetObjectArrayElement(array, index);
	if (!itemstack) return CItemStack();
	return CItemStack(itemstack);

}
