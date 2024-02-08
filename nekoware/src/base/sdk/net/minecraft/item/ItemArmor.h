#pragma once
#include "ItemStack.h"
#include "item.h"
#include "../../../Object.h"

class CItemArmor : public CItem
{
public:
	using CItem::CItem;
	CItemArmor(CItem item, JNIEnv* env = Java::Env);
	int getColor(CItemStack stack, JNIEnv* env = Java::Env);
};