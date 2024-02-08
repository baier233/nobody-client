#pragma once

#include "../../world/World.h"
#include "../../../../java/util/Set.h"

class CWorldClient :public CWorld
{
public:
	using CWorld::CWorld;
	jclass EntityPlayer;
	Set GetEntityList();
	int getIDFromBlock(jobject block);
};

