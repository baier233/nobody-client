#pragma once

#include "../../../../Object.h"
#include "../../item/ItemStack.h"

class CInventoryPlayer :public Object
{

public:
	using Object::Object;
	CItemStack GetCurrentItem(JNIEnv* env = Java::GetInstance()->Env);
	void SetCurrentItem(int index, JNIEnv* env = Java::GetInstance()->Env);
	CItemStack GetIndexItem(int index, JNIEnv* env = Java::GetInstance()->Env);
	CItemStack GetStackInSlot(int index, JNIEnv* env = Java::GetInstance()->Env);
	CItemStack GetArmorItem(int index, JNIEnv* env = Java::GetInstance()->Env);
};