#include "EntityLivingBase.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

//CEntityLivingBase::CEntityLivingBase()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::entityLivingBase_class;
//}
//
//jclass CEntityLivingBase::getClass()
//{
//	return this->Class;
//}
//
//jobject CEntityLivingBase::getInstance()
//{
//	return this->Instance;
//}

float CEntityLivingBase::GetHealth(JNIEnv* env )
{
	return env->CallFloatMethod(this->getInstance(), StrayCache::entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth(JNIEnv* env )
{
	return env->CallFloatMethod(this->getInstance(), StrayCache::entityLivingBase_getMaxHealth);
}

float CEntityLivingBase::getMoveStrafe(JNIEnv* env )
{

	return env->GetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveStrafe);
}

float CEntityLivingBase::getMoveForward(JNIEnv* env )
{
	return env->GetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveForward);

}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity, JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		if (!Java::Env->IsInstanceOf(entity, StrayCache::entityLivingBase_class)) return false;
	}
	return env->CallBooleanMethod(this->getInstance(), StrayCache::entityLivingBase_canEntityBeSeen, entity);
}


bool CEntityLivingBase::isPlayerSleeping(JNIEnv* env )
{
	return env->CallBooleanMethod(this->getInstance(), StrayCache::entityLivingBase_isPlayerSleeping);
}

int CEntityLivingBase::getHurtTime(JNIEnv* env ) {
	return env->GetIntField(this->getInstance(), StrayCache::entityLivingBase_hurttime);
}

void CEntityLivingBase::swingItem(JNIEnv* env )
{
	env->CallVoidMethod(this->getInstance(), StrayCache::entityLivingBase_swingItem);
}

void CEntityLivingBase::jump(JNIEnv* env )
{
	env->CallVoidMethod(this->getInstance(), StrayCache::entityLivingBase_jump);
}

void CEntityLivingBase::setMoveStrafe(float i, JNIEnv* env )
{
	env->SetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveStrafe, i);
}

void CEntityLivingBase::setMoveForward(float i, JNIEnv* env )
{
	env->SetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveForward, i);

}
