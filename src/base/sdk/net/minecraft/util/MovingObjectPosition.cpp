#include "MovingObjectPosition.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"
#include "../../../SDK.h"


CVec3 CMovingObjectPosition::GetBlockPosition(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		return CVec3{};
	}
	return CVec3(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->movingObjectPosition_hitVec));
}

CBlock CMovingObjectPosition::GetBlock(JNIEnv* env)
{
	int x, y, z{};
	x = Java::GetInstance()->Env->GetIntField(this->instance, StrayCache::GetInstance()->movingObjectPosition_blockX);
	y = Java::GetInstance()->Env->GetIntField(this->instance, StrayCache::GetInstance()->movingObjectPosition_blockY);
	z = Java::GetInstance()->Env->GetIntField(this->instance, StrayCache::GetInstance()->movingObjectPosition_blockZ);
	return SDK::GetInstance()->Minecraft->theWorld->GetBlock(x,y,z);
}

bool CMovingObjectPosition::IsTypeOfBlock(JNIEnv* env )
{
	if (!this->getInstance()) return true;

	if (Base::version == FORGE_1_18_1)
	{
		jobject typeOfHit = env->CallObjectMethod(this->instance, StrayCache::GetInstance()->hitResult_getType);
		if (!typeOfHit) return false;

		jclass movingObjectType = env->GetObjectClass(typeOfHit);
		if (!movingObjectType) return false;

		auto block = env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/world/phys/HitResult$Type;");
		if (!block) return false;
		jobject object = env->GetStaticObjectField(movingObjectType, block);
		if (!object) return false;

		return env->IsSameObject(object, typeOfHit);
	}



	jobject typeOfHit = env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->movingObjectPosition_typeOfHit);
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


	if (Base::version == FORGE_1_18_1)
	{
		jobject typeOfHit = env->CallObjectMethod(this->instance, StrayCache::GetInstance()->hitResult_getType);
		if (!typeOfHit) return false;

		jclass movingObjectType = env->GetObjectClass(typeOfHit);
		if (!movingObjectType) return false;

		auto block = env->GetStaticFieldID(movingObjectType, "ENTITY", "Lnet/minecraft/world/phys/HitResult$Type;");
		if (!block) return false;
		jobject object = env->GetStaticObjectField(movingObjectType, block);
		if (!object) return false;

		return env->IsSameObject(object, typeOfHit);
	}


	jobject typeOfHit = env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->movingObjectPosition_typeOfHit);
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
	if (Base::version == FORGE_1_18_1)
	{
		if (this->IsTypeOfBlock())
		{

		}
	}
	return BlockPos(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->movingObjectPosition_blockPos));
}
