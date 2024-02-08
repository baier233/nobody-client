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
	CVec3 GetBlockPosition(JNIEnv* env = Java::Env);
	bool IsTypeOfBlock(JNIEnv* env = Java::Env);
	bool IsTypeOfEntity(JNIEnv* env = Java::Env);
	BlockPos getBlockPos(JNIEnv* env = Java::Env);
};

