#pragma once
#include "../../../Object.h"
#include "Vec3.h"
#include "BlockPos.h"

class CMovingObjectPosition :public Object
{
	//CMovingObjectPosition();
	//CMovingObjectPosition(jobject instance);

	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	CVec3 GetBlockPosition();
	bool IsTypeOfBlock();
	bool IsTypeOfEntity();
	BlockPos getBlockPos();
};

