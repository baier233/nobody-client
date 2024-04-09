#pragma once

#include "../../../Object.h"
#include "../../../../util/math/geometry.h"
#include "../util/AxisAlignedBB.h"
#include "../../../../util/logger.h"
class CEntity : public Object
{
public:
	using Object::Object;

	std::string GetName(JNIEnv* env = Java::GetInstance()->Env);

	Object GetObjectName(JNIEnv* env = Java::GetInstance()->Env);

	Vector3 GetPos(JNIEnv* env = Java::GetInstance()->Env) const;
	Vector3 GetEyePos(JNIEnv* env = Java::GetInstance()->Env);
	Vector3 GetLastTickPos(JNIEnv* env = Java::GetInstance()->Env);

	void setMotion(Vector3 motion, JNIEnv* env = Java::GetInstance()->Env);
	void setSprint(bool state, JNIEnv* env = Java::GetInstance()->Env);

	Vector3 getMotion(JNIEnv* env = Java::GetInstance()->Env);

	bool isOnGround(JNIEnv* env = Java::GetInstance()->Env);
	bool inWater(JNIEnv* env = Java::GetInstance()->Env);
	bool isDead(JNIEnv* env = Java::GetInstance()->Env);
	bool isInvisible(JNIEnv* env = Java::GetInstance()->Env);
	float fallDistance(JNIEnv* env = Java::GetInstance()->Env);
	void setFallDistance(float i, JNIEnv* env = Java::GetInstance()->Env);
	int ticksExisted(JNIEnv* env = Java::GetInstance()->Env);
	void setPos(double x, double y, double z, JNIEnv* env = Java::GetInstance()->Env);
	void setOnGround(bool state, JNIEnv* env = Java::GetInstance()->Env);

	bool IsSneaking(JNIEnv* env = Java::GetInstance()->Env);
	void setSneaking(bool state, JNIEnv* env = Java::GetInstance()->Env);

	float GetHeight(JNIEnv* env = Java::GetInstance()->Env);
	float GetWidth(JNIEnv* env = Java::GetInstance()->Env);

	float GetDistanceWalkedModified(JNIEnv* env = Java::GetInstance()->Env);
	float GetPrevDistanceWalkedModified(JNIEnv* env = Java::GetInstance()->Env);

	float GetRotationYaw(JNIEnv* env = Java::GetInstance()->Env);
	float GetRotationPitch(JNIEnv* env = Java::GetInstance()->Env);

	float GetPrevRotationYaw(JNIEnv* env = Java::GetInstance()->Env);
	float GetPrevRotationPitch(JNIEnv* env = Java::GetInstance()->Env);

	float GetEyeHeight(JNIEnv* env = Java::GetInstance()->Env);

	jobject getUniqueID(JNIEnv* env = Java::GetInstance()->Env);

	Vector2 GetAngles(JNIEnv* env = Java::GetInstance()->Env);
	Vector2 GetPrevAngles(JNIEnv* env = Java::GetInstance()->Env);

	void SetAngles(Vector2 angles, JNIEnv* env = Java::GetInstance()->Env);

	CAxisAlignedBB GetBB(JNIEnv* env = Java::GetInstance()->Env);
	void SetBB(BoundingBox bb, JNIEnv* env = Java::GetInstance()->Env);
};