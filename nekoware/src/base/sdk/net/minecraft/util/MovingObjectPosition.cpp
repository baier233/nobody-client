#include "MovingObjectPosition.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

//CMovingObjectPosition::CMovingObjectPosition()
//{
//	if (!StrayCache::initialized) StrayCache::Initialize();
//	this->Class = StrayCache::movingObjectPosition_class;
//}
//
//CMovingObjectPosition::CMovingObjectPosition(jobject instance) : CMovingObjectPosition()
//{
//	this->Instance = instance;
//}
//
//jclass CMovingObjectPosition::getClass()
//{
//	return this->Class;
//}
//
//jobject CMovingObjectPosition::getInstance()
//{
//	return this->Instance;
//}

CVec3 CMovingObjectPosition::GetBlockPosition()
{
	return CVec3(Java::Env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_hitVec));
}

bool CMovingObjectPosition::IsTypeOfBlock()
{
	if (!this->getInstance()) return true;
	
	jobject typeOfHit = Java::Env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = Java::Env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;

	jfieldID block;

	if (Base::version == 1)
	{
		block = Java::Env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/math/RayTraceResult$Type;");
	}
	else {
		block = Java::Env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");

	}
	if (!block) return false;
	jobject object = Java::Env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return Java::Env->IsSameObject(object, typeOfHit);
}

bool CMovingObjectPosition::IsTypeOfEntity()
{
	jobject typeOfHit = Java::Env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = Java::Env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;
	jfieldID block;
	if (Base::version == 1)
	{
		block = Java::Env->GetStaticFieldID(movingObjectType, "ENTITY", "Lnet/minecraft/util/math/RayTraceResult$Type;");
	}
	else {
		block = Java::Env->GetStaticFieldID(movingObjectType, "ENTITY", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	}
	if (!block) return false;
	jobject object = Java::Env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return Java::Env->IsSameObject(object, typeOfHit);
}

BlockPos CMovingObjectPosition::getBlockPos()
{
	return BlockPos(Java::Env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_blockPos));
}
