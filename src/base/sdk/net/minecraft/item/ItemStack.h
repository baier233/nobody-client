#pragma once
#include "../../../Object.h"
#include "../block/Block.h"
#include "item.h"
#include "../block/state/IBlockState.h"

class CItemStack : public Object
{
public:
	using Object::Object;
	CItem GetItem(JNIEnv* env = Java::Env);

	float GetStrVsBlock(CBlock block, JNIEnv* env = Java::Env);
	float GetStrVsBlock(CIBlockState block, JNIEnv* env = Java::Env);
};