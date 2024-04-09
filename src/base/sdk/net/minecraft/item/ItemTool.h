#pragma once
#pragma once
#include "../../../Object.h"
#include "ItemArmor.h"
#include "../block/Block.h"
#include "item.h"
class CItemTool : public CItem
{

public:
	using CItem::CItem;
	float GetStrVsBlock(CItemStack stack, CBlock state, JNIEnv* env = Java::GetInstance()->Env);
};