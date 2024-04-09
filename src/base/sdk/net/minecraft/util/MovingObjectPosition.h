#pragma once
#include "../../../Object.h"
#include "Vec3.h"
#include "BlockPos.h"
#include "../block/Block.h"

class CMovingObjectPosition :public Object
{
	//CMovingObjectPosition();
	//CMovingObjectPosition(jobject instance);

	//jclass getClass();
	//jobject getInstance();
public:
	using Object::Object;
	CVec3 GetBlockPosition(JNIEnv* env = Java::GetInstance()->Env);
	CBlock GetBlock(JNIEnv* env = Java::GetInstance()->Env);
	bool IsTypeOfBlock(JNIEnv* env = Java::GetInstance()->Env);
	bool IsTypeOfEntity(JNIEnv* env = Java::GetInstance()->Env);
	BlockPos getBlockPos(JNIEnv* env = Java::GetInstance()->Env);
};

