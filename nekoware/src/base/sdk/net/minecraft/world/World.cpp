#include "World.h"

#include "../../../sdk.h"
#include "../../../../java/java.h"

#include "../util/Vec3.h"
#include "../util/MovingObjectPosition.h"

#include "../../../../util/logger.h"



List CWorld::GetPlayerList()
{
	return List(Java::Env->GetObjectField(instance, StrayCache::world_playerEntities));
}

Vector3 CWorld::rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock)
{
	jclass cls = StrayCache::vec3_class;
	jmethodID init = Java::Env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = Java::Env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = Java::Env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	CMovingObjectPosition movingObjPos = CMovingObjectPosition(Java::Env->CallObjectMethod(
		this->getInstance(),
		StrayCache::world_rayTraceBlocks,
		j_from,
		j_to,
		stopOnLiquid,
		ignoreBlockWithoutBoundingBox,
		returnLastUncollidableBlock
	));

	if (!movingObjPos.check())
	{
		Java::Env->DeleteLocalRef(j_to);
		Java::Env->DeleteLocalRef(j_from);
		Java::Env->DeleteLocalRef(cls);
		return Vector3{};
	}


	Vector3 blockPos = movingObjPos.GetBlockPosition().GetNativeVector3();
	Java::Env->DeleteLocalRef(j_to);
	Java::Env->DeleteLocalRef(j_from);
	Java::Env->DeleteLocalRef(cls);
	return blockPos;
}

CChunk CWorld::getChunkFromChunkCoords(jint chunkX, jint chunkZ)
{
	return CChunk(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::world_getChunkFromChunkCoords));
}

CIBlockState CWorld::getBlockState(BlockPos pos) {
	return CIBlockState(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::world_getBlockState, pos.getInstance()));
}

bool CWorld::isAirBlock(double x, double y, double z)
{
	if (JNIHelper::IsForge()) {
		jclass blockPosClass = StrayCache::blockPos_class;
		jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
		jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

		return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos);

	}
	jclass blockPosClass = StrayCache::blockPos_class;
	jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos);
}

bool CWorld::isAirBlock(BlockPos pos)
{

	if (JNIHelper::IsForge()) {
		return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());

	}
	return Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());
}

int CWorld::getBlock(double x, double y, double z)
{
	if (this->getInstance() == NULL)return 0;
	if (Base::version == FORGE_1_7_10) {
		//TODO: Make this work for 1.7.10
		return 0;
	}
	jclass blockPosClass = StrayCache::blockPos_class;
	jmethodID blockPosConstructor = Java::Env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	jobject blockpos = Java::Env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

	jboolean isAir = Java::Env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos);
	if (isAir) {
		Java::Env->DeleteLocalRef(blockpos);
		return 0;
	}

	const auto blockState = Java::Env->CallObjectMethod(this->getInstance(), StrayCache::world_getBlockState, blockpos);
	const auto block = Java::Env->CallObjectMethod(blockState, StrayCache::iBlockState_getBlock);
	int blockID = Java::Env->CallIntMethod(StrayCache::block_class, StrayCache::block_getIdFromBlock, block);

	//free memory
	Java::Env->DeleteGlobalRef(blockpos);
	Java::Env->DeleteLocalRef(blockState);
	Java::Env->DeleteLocalRef(block);

	return blockID;
}
