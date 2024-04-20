#pragma once

#include "Entity.h"

class CEntityLivingBase : public CEntity
{
public:
	using CEntity::CEntity;
	float GetHealth(JNIEnv* env = Java::Env);
	float GetMaxHealth(JNIEnv* env = Java::Env);
	float getMoveStrafe(JNIEnv* env = Java::Env);
	float getMoveForward(JNIEnv* env = Java::Env);
	bool CanEntityBeSeen(jobject entity, JNIEnv* env = Java::Env);
	bool isPlayerSleeping(JNIEnv* env = Java::Env);
	int getHurtTime(JNIEnv* env = Java::Env);
	void swingItem(JNIEnv* env = Java::Env);
	void jump(JNIEnv* env = Java::Env);
	void setMoveStrafe(float i, JNIEnv* env = Java::Env);
	void setMoveForward(float i, JNIEnv* env = Java::Env);
};

