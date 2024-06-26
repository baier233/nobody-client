#pragma once

#include "../../world/World.h"
#include "../../../../java/util/Set.h"

class CWorldClient :public CWorld
{
public:
	using CWorld::CWorld;
	jclass EntityPlayer;
	Set GetEntityList(JNIEnv* env = Java::Env);
	int getIDFromBlock(jobject block, JNIEnv* env = Java::Env);
};

