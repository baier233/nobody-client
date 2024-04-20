#pragma once

#include "../../../../Object.h"
#include "../../../../../util/math/geometry.h"
#include "../Block.h"
class CIBlockState : public Object
{
public:
	using Object::Object;

	CBlock getBlock(JNIEnv* env = Java::Env);
};

