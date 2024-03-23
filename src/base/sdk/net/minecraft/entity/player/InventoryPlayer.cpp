#include "InventoryPlayer.h"

#include "../../../../strayCache.h"
#include "../../../../java/util/List.h"
#include "../../util/NonNullList.h"
//CInventoryPlayer::CInventoryPlayer()
//{
//	if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//	this->Class = StrayCache::GetInstance()->inventoryPlayer_class;
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

CItemStack CInventoryPlayer::GetCurrentItem(JNIEnv* env )
{
	return CItemStack(env->CallObjectMethod(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_getCurrentItem));
}

void CInventoryPlayer::SetCurrentItem(int index, JNIEnv* env )
{
	env->SetIntField(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_currentItem, index);
}

CItemStack CInventoryPlayer::GetIndexItem(int index, JNIEnv* env )
{
	jobject mainInventory = env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_mainInv);
	jobject itemstack = env->GetObjectArrayElement((jobjectArray)mainInventory, index);
	return CItemStack(itemstack);

}
CItemStack CInventoryPlayer::GetStackInSlot(int index, JNIEnv* env )
{
	return CItemStack(env->CallObjectMethod(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_getStackInSlot, index));

}

CItemStack CInventoryPlayer::GetArmorItem(int index, JNIEnv* env )
{

	if (!isValid() || isNULL())
	{
		return CItemStack{};
	}
	jobjectArray array;
	if (Base::version == FORGE_1_12_2 || Base::version == LUNAR_1_12_2)
	{
		array = CNonNullList(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_armorInv)).getList().toArray();
	}
	else {
		array = (jobjectArray)env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->inventoryPlayer_armorInv);
	}
	if (!array) return CItemStack();
	jobject itemstack = env->GetObjectArrayElement(array, index);
	if (!itemstack) return CItemStack();
	return CItemStack(itemstack);

}
