#pragma once

#include "Entity.h"

class CEntityLivingBase : public CEntity
{
public:
	using CEntity::CEntity;
	float GetHealth(JNIEnv* env = Java::GetInstance()->Env);
	float GetMaxHealth(JNIEnv* env = Java::GetInstance()->Env);
	float getMoveStrafe(JNIEnv* env = Java::GetInstance()->Env);
	float getMoveForward(JNIEnv* env = Java::GetInstance()->Env);
	bool CanEntityBeSeen(jobject entity, JNIEnv* env = Java::GetInstance()->Env);
	bool isPlayerSleeping(JNIEnv* env = Java::GetInstance()->Env);
	int getHurtTime(JNIEnv* env = Java::GetInstance()->Env);
	void swingItem(JNIEnv* env = Java::GetInstance()->Env);
	void jump(JNIEnv* env = Java::GetInstance()->Env);
	void setMoveStrafe(float i, JNIEnv* env = Java::GetInstance()->Env);
	void setMoveForward(float i, JNIEnv* env = Java::GetInstance()->Env);
};

