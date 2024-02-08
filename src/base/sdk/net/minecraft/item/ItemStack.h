#pragma once
#include "../../../Object.h"
#include "../block/Block.h"
#include "item.h"
#include "../block/state/IBlockState.h"

class CItemStack : public Object
{
public:
	using Object::Object;
	CItem GetItem();
	
	float GetStrVsBlock(CBlock block);
	float GetStrVsBlock(CIBlockState block);
};