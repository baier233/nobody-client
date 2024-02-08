#pragma once

#include "../../../Object.h"
#include "../../../../util/math/geometry.h"
#include "../util/AxisAlignedBB.h"
#include "../../../../util/logger.h"
class CEntity : public Object
{
public:
	using Object::Object;

	std::string GetName(JNIEnv* env = Java::Env);

	Object GetObjectName(JNIEnv* env = Java::Env);

	Vector3 GetPos(JNIEnv* env = Java::Env) const;
	Vector3 GetEyePos(JNIEnv* env = Java::Env);
	Vector3 GetLastTickPos(JNIEnv* env = Java::Env);

	void setMotion(Vector3 motion, JNIEnv* env = Java::Env);
	void setSprint(bool state, JNIEnv* env = Java::Env);

	Vector3 getMotion(JNIEnv* env = Java::Env);

	bool isOnGround(JNIEnv* env = Java::Env);
	bool inWater(JNIEnv* env = Java::Env);
	bool isDead(JNIEnv* env = Java::Env);
	bool isInvisible(JNIEnv* env = Java::Env);
	float fallDistance(JNIEnv* env = Java::Env);
	void setFallDistance(float i, JNIEnv* env = Java::Env);
	int ticksExisted(JNIEnv* env = Java::Env);
	void setPos(double x, double y, double z, JNIEnv* env = Java::Env);
	void setOnGround(bool state, JNIEnv* env = Java::Env);

	bool IsSneaking(JNIEnv* env = Java::Env);
	void setSneaking(bool state, JNIEnv* env = Java::Env);

	float GetHeight(JNIEnv* env = Java::Env);
	float GetWidth(JNIEnv* env = Java::Env);

	float GetDistanceWalkedModified(JNIEnv* env = Java::Env);
	float GetPrevDistanceWalkedModified(JNIEnv* env = Java::Env);

	float GetRotationYaw(JNIEnv* env = Java::Env);
	float GetRotationPitch(JNIEnv* env = Java::Env);

	float GetPrevRotationYaw(JNIEnv* env = Java::Env);
	float GetPrevRotationPitch(JNIEnv* env = Java::Env);

	jobject getUniqueID(JNIEnv* env = Java::Env);

	Vector2 GetAngles(JNIEnv* env = Java::Env);
	Vector2 GetPrevAngles(JNIEnv* env = Java::Env);

	void SetAngles(Vector2 angles, JNIEnv* env = Java::Env);

	CAxisAlignedBB GetBB(JNIEnv* env = Java::Env);
	void SetBB(BoundingBox bb, JNIEnv* env = Java::Env);
};