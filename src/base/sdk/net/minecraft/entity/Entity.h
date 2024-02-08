#pragma once

#include "../../../Object.h"
#include "../../../../util/math/geometry.h"
#include "../util/AxisAlignedBB.h"
#include "../../../../util/logger.h"
class CEntity : public Object
{
public:
	using Object::Object;

	std::string GetName();

	Object GetObjectName();

	Vector3 GetPos() const;
	Vector3 GetEyePos();
	Vector3 GetLastTickPos();

	void setMotion(Vector3 motion);
	void setSprint(bool state);

	Vector3 getMotion();

	bool isOnGround();
	bool inWater();
	bool isDead();
	bool isInvisible();
	float fallDistance();
	void setFallDistance(float i);
	int ticksExisted();
	void setPos(double x, double y, double z);
	void setOnGround(bool state);

	bool IsSneaking();
	void setSneaking(bool state);

	float GetHeight();
	float GetWidth();

	float GetDistanceWalkedModified();
	float GetPrevDistanceWalkedModified();

	float GetRotationYaw();
	float GetRotationPitch();

	float GetPrevRotationYaw();
	float GetPrevRotationPitch();

	jobject getUniqueID();

	Vector2 GetAngles();
	Vector2 GetPrevAngles();

	void SetAngles(Vector2 angles);

	CAxisAlignedBB GetBB();
	void SetBB(BoundingBox bb);
};