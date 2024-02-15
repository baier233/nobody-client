#pragma once
#include "../../../Object.h"
#include "../util/BlockPos.h"
class CTileEntity : public Object
{
public:
	using Object::Object;
	BlockPos getPos();
};