#include "EntityLivingBase.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

//CEntityLivingBase::CEntityLivingBase()
//{
//	if (!StrayCache::GetInstance()->initialized) StrayCache::GetInstance()->Initialize();
//	this->Class = StrayCache::GetInstance()->entityLivingBase_class;
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
	return env->CallFloatMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth(JNIEnv* env )
{
	return env->CallFloatMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_getMaxHealth);
}

float CEntityLivingBase::getMoveStrafe(JNIEnv* env )
{

	return env->GetFloatField(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_moveStrafe);
}

float CEntityLivingBase::getMoveForward(JNIEnv* env )
{
	return env->GetFloatField(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_moveForward);

}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity, JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		if (!Java::GetInstance()->Env->IsInstanceOf(entity, StrayCache::GetInstance()->entityLivingBase_class)) return false;
	}
	return env->CallBooleanMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_canEntityBeSeen, entity);
}


bool CEntityLivingBase::isPlayerSleeping(JNIEnv* env )
{
	return env->CallBooleanMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_isPlayerSleeping);
}

int CEntityLivingBase::getHurtTime(JNIEnv* env ) {
	return env->GetIntField(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_hurttime);
}

void CEntityLivingBase::swingItem(JNIEnv* env )
{
	env->CallVoidMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_swingItem);
}

void CEntityLivingBase::jump(JNIEnv* env )
{
	env->CallVoidMethod(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_jump);
}

void CEntityLivingBase::setMoveStrafe(float i, JNIEnv* env )
{
	env->SetFloatField(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_moveStrafe, i);
}

void CEntityLivingBase::setMoveForward(float i, JNIEnv* env )
{
	env->SetFloatField(this->getInstance(), StrayCache::GetInstance()->entityLivingBase_moveForward, i);

}
