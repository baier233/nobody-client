#include "Entity.h"
#include "../../../../java/java.h"
#include "../../../java/lang/String.h"
#include "../../../strayCache.h"

#include "../../../../util/logger.h"
#include "../util/Vec3.h"
#include "EntityLivingBase.h"

std::string CEntity::GetName(JNIEnv* env)
{
	if (Base::version == FORGE_1_18_1)
	{
		return "UnImplement";
	}
	return "";
	if (!this->check())
	{
		return "";
	}
	auto data = this->GetObjectName();
	if (!data.check())return"";

	std::string res = JNIHelper::jstring2string(env, static_cast<jstring>(data.getInstance()));
	std::string gbkstr = JNIHelper::UtfToGbk(res.c_str());
	data.clear();
	return gbkstr;
}

Object CEntity::GetObjectName(JNIEnv* env)
{
	if (!this->check())
	{
		return Object{};
	}
	jobject data = env->CallObjectMethod(this->getInstance(), StrayCache::entity_getName);
	if (data == nullptr)return Object();
	return Object(data);
}

Vector3 CEntity::GetPos(JNIEnv* env) const
{

	if (!this->getInstance())
	{
		return Vector3{ 0,0,0 };
	}

	if (Base::version == FORGE_1_18_1)
	{
		return CVec3(env->GetObjectField(this->getInstance(), StrayCache::entity_position)).GetNativeVector3();
	}

	return Vector3{
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_posX),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_posY),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_posZ)
	};
}

Vector3 CEntity::GetEyePos(JNIEnv* env)
{
	if (!this->getInstance())
	{
		return Vector3{ 0,0,0 };
	}
	Vector3 pos = GetPos();
	return Vector3{
		pos.x,
		(float)(double)(pos.y + (this->GetHeight() * 0.85)),
		pos.z
	};
}

Vector3 CEntity::GetLastTickPos(JNIEnv* env)
{
	return Vector3{
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosX),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosY),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_lastTickPosZ)
	};
}

void CEntity::setMotion(Vector3 motion, JNIEnv* env) {
	if (Base::version == FORGE_1_18_1)
	{

		auto vec3 = CVec3(Java::Env->GetObjectField(this->instance, StrayCache::entity_deltaMovement));
		if (motion.x != 100000000000) {
			env->SetDoubleField(vec3.getInstance(), StrayCache::vec3_xCoord, motion.x);
		}
		if (motion.y != 100000000000) {
			env->SetDoubleField(vec3.getInstance(), StrayCache::vec3_yCoord, motion.y);
		}
		if (motion.z != 100000000000) {
			env->SetDoubleField(vec3.getInstance(), StrayCache::vec3_zCoord, motion.z);
		}
	}
	if (motion.x != 100000000000) {
		env->SetDoubleField(this->getInstance(), StrayCache::entity_motionX, motion.x);
	}
	if (motion.y != 100000000000) {
		env->SetDoubleField(this->getInstance(), StrayCache::entity_motionY, motion.y);
	}
	if (motion.z != 100000000000) {
		env->SetDoubleField(this->getInstance(), StrayCache::entity_motionZ, motion.z);
	}
}

void CEntity::setSprint(bool state, JNIEnv* env)
{
	env->CallVoidMethod(this->getInstance(), StrayCache::entity_setSprint, state);
}

Vector3 CEntity::getMotion(JNIEnv* env) {
	if (Base::version == FORGE_1_18_1)
	{
		return CVec3(Java::Env->GetObjectField(this->instance,StrayCache::entity_deltaMovement)).GetNativeVector3();
	}
	return Vector3{
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_motionX),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_motionY),
		(float)(double)env->GetDoubleField(this->getInstance(), StrayCache::entity_motionZ)
	};
}

bool CEntity::isOnGround(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return false;
	return env->GetBooleanField(this->getInstance(), StrayCache::entity_onGround);
}

bool CEntity::inWater(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return false;
	return env->CallBooleanMethod(this->getInstance(), StrayCache::entity_inWater);

}

bool CEntity::isDead(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return true;
	if (Base::version == FORGE_1_18_1)
	{
		return CEntityLivingBase(this->getInstance()).GetHealth() <= 0;
	}
	return env->GetBooleanField(this->getInstance(), StrayCache::entity_isDead);
}

bool CEntity::isInvisible(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return true;
	return env->CallBooleanMethod(this->getInstance(), StrayCache::entity_isInvisible);
}

float CEntity::fallDistance(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_fallDistance);
}

void CEntity::setFallDistance(float i, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	env->SetFloatField(this->getInstance(), StrayCache::entity_fallDistance, i);

}

int CEntity::ticksExisted(JNIEnv* env)
{
	return env->GetIntField(this->getInstance(), StrayCache::entity_ticksExisted);

}

void CEntity::setPos(double x, double y, double z, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	env->CallVoidMethod(this->getInstance(), StrayCache::entity_setPosition, x, y, z);

}

void CEntity::setOnGround(bool state, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	env->SetBooleanField(this->getInstance(), StrayCache::entity_onGround, state);
}

bool CEntity::IsSneaking(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return false;
	return env->CallBooleanMethod(this->getInstance(), StrayCache::entity_isSneaking);
}

void CEntity::setSneaking(bool state, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	env->CallVoidMethod(this->getInstance(), StrayCache::entity_setSneaking, state);
}

float CEntity::GetHeight(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	if (Base::version == FORGE_1_18_1)
	{
		return env->CallFloatMethod(this->instance, StrayCache::entity_getBBHeight);
	}
	return env->GetFloatField(this->getInstance(), StrayCache::entity_height);
}

float CEntity::GetWidth(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_width);
}

float CEntity::GetDistanceWalkedModified(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_distanceWalkedModified);
}

float CEntity::GetPrevDistanceWalkedModified(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_prevDistanceWalkedModified);
}

float CEntity::GetRotationYaw(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_rotationYaw);
}

float CEntity::GetRotationPitch(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_rotationPitch);
}

float CEntity::GetPrevRotationYaw(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_prevRotationYaw);
}

float CEntity::GetPrevRotationPitch(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;
	return env->GetFloatField(this->getInstance(), StrayCache::entity_prevRotationPitch);
}

float CEntity::GetEyeHeight(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return NULL;

	return env->GetFloatField(this->instance,StrayCache::entity_eyeHeight);
}

jobject CEntity::getUniqueID(JNIEnv* env)
{
	return env->CallObjectMethod(this->getInstance(), StrayCache::entity_getUniqueID);
}

Vector2 CEntity::GetAngles(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return Vector2{};
	return Vector2(CEntity::GetRotationYaw(), CEntity::GetRotationPitch());
}

Vector2 CEntity::GetPrevAngles(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return Vector2{};
	return Vector2(CEntity::GetPrevRotationYaw(), CEntity::GetPrevRotationPitch());
}

void CEntity::SetAngles(Vector2 angles, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	env->SetFloatField(this->getInstance(), StrayCache::entity_rotationYaw, angles.x);
	env->SetFloatField(this->getInstance(), StrayCache::entity_rotationPitch, angles.y);
};

CAxisAlignedBB CEntity::GetBB(JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return CAxisAlignedBB{};
	return CAxisAlignedBB(
		env->GetObjectField(this->getInstance(), StrayCache::entity_boundingBox)
	);
}

void CEntity::SetBB(BoundingBox bb, JNIEnv* env)
{
	if (!this->isValid() || this->isNULL()) return;
	this->GetBB().SetBoundingBox(bb);
}
