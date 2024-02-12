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

CVec3 CMovingObjectPosition::GetBlockPosition(JNIEnv* env )
{
	return CVec3(env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_hitVec));
}

bool CMovingObjectPosition::IsTypeOfBlock(JNIEnv* env )
{
	if (!this->getInstance()) return true;

	jobject typeOfHit = env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;

	jfieldID block;

	if (Base::version == FORGE_1_12_2 || Base::version == LUNAR_1_12_2)
	{
		block = env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/math/RayTraceResult$Type;");
	}
	else {
		block = env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");

	}
	if (!block) return false;
	jobject object = env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return env->IsSameObject(object, typeOfHit);
}

bool CMovingObjectPosition::IsTypeOfEntity(JNIEnv* env )
{
	jobject typeOfHit = env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;
	jfieldID block;
	if (Base::version == FORGE_1_12_2 || Base::version == LUNAR_1_12_2)
	{
		block = env->GetStaticFieldID(movingObjectType, "ENTITY", "Lnet/minecraft/util/math/RayTraceResult$Type;");
	}
	else {
		block = env->GetStaticFieldID(movingObjectType, "ENTITY", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	}
	if (!block) return false;
	jobject object = env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return env->IsSameObject(object, typeOfHit);
}

BlockPos CMovingObjectPosition::getBlockPos(JNIEnv* env )
{
	return BlockPos(env->GetObjectField(this->getInstance(), StrayCache::movingObjectPosition_blockPos));
}
