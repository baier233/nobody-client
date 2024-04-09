#pragma once
#include "ItemStack.h"
#include "item.h"
#include "../../../Object.h"

class CItemArmor : public CItem
{
public:
	using CItem::CItem;
	CItemArmor(CItem item, JNIEnv* env = Java::GetInstance()->Env);
	int getColor(CItemStack stack, JNIEnv* env = Java::GetInstance()->Env);
};