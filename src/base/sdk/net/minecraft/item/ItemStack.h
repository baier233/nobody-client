#pragma once
#include "../../../Object.h"
#include "../block/Block.h"
#include "item.h"
#include "../block/state/IBlockState.h"

class CItemStack : public Object
{
public:
	using Object::Object;
	CItem GetItem(JNIEnv* env = Java::GetInstance()->Env);

	float GetStrVsBlock(CBlock block, JNIEnv* env = Java::GetInstance()->Env);
	float GetStrVsBlock(CIBlockState block, JNIEnv* env = Java::GetInstance()->Env);
};