#pragma once

#include "Entity.h"

class CEntityLivingBase : public CEntity
{
public:
	using CEntity::CEntity;
	float GetHealth();
	float GetMaxHealth();
	float getMoveStrafe();
	float getMoveForward();
	bool CanEntityBeSeen(jobject entity);
	bool isPlayerSleeping();
	int getHurtTime();
	void swingItem();
	void jump();
	void setMoveStrafe(float i);
	void setMoveForward(float i);
};

