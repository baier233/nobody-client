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

float CEntityLivingBase::GetHealth()
{
	return Java::Env->CallFloatMethod(this->getInstance(), StrayCache::entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth()
{
	return Java::Env->CallFloatMethod(this->getInstance(), StrayCache::entityLivingBase_getMaxHealth);
}

float CEntityLivingBase::getMoveStrafe()
{

	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveStrafe);
}

float CEntityLivingBase::getMoveForward()
{
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveForward);

}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity) 
{
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entityLivingBase_canEntityBeSeen, entity);
}


bool CEntityLivingBase::isPlayerSleeping()
{
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::entityLivingBase_isPlayerSleeping);
}

int CEntityLivingBase::getHurtTime() {
	return Java::Env->GetIntField(this->getInstance(), StrayCache::entityLivingBase_hurttime);
}

void CEntityLivingBase::swingItem()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::entityLivingBase_swingItem);
}

void CEntityLivingBase::jump()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::entityLivingBase_jump);
}

void CEntityLivingBase::setMoveStrafe(float i)
{
	Java::Env->SetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveStrafe, i);
}

void CEntityLivingBase::setMoveForward(float i)
{
	Java::Env->SetFloatField(this->getInstance(), StrayCache::entityLivingBase_moveForward, i);

}
