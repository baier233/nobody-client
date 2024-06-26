#include "World.h"

#include "../../../sdk.h"
#include "../../../../java/java.h"

#include "../util/Vec3.h"
#include "../util/MovingObjectPosition.h"

#include "../../../../util/logger.h"



List CWorld::GetPlayerList(JNIEnv* env)
{
	if (Base::version == FORGE_1_18_1)
	{
		return List(env->GetObjectField(this->instance, StrayCache::clientLevel_players));
	}
	return List(env->GetObjectField(instance, StrayCache::world_playerEntities));
}

List CWorld::GetLoadedEntityList(JNIEnv* env)
{
	return List(env->GetObjectField(instance, StrayCache::world_loadedEntityList));
}

List CWorld::GetLoadedTileEntityList(JNIEnv* env)
{
	return List(env->GetObjectField(instance, StrayCache::world_loadedTileEntityList));
}

CBlock CWorld::GetBlock(int x, int y, int z, JNIEnv* env)
{
	return CBlock(Java::Env->CallObjectMethod(this->instance, StrayCache::world_getBlock, x, y, z));
}

Vector3 CWorld::rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock, JNIEnv* env)
{
	if (Base::version == FORGE_1_18_1)
	{
		return Vector3{};
	}
	jclass cls = StrayCache::vec3_class;
	jmethodID init = env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	CMovingObjectPosition movingObjPos = CMovingObjectPosition(env->CallObjectMethod(
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
		env->DeleteLocalRef(j_to);
		env->DeleteLocalRef(j_from);
		env->DeleteLocalRef(cls);
		return Vector3{};
	}


	Vector3 blockPos = movingObjPos.GetBlockPosition().GetNativeVector3();
	env->DeleteLocalRef(j_to);
	env->DeleteLocalRef(j_from);
	env->DeleteLocalRef(cls);
	return blockPos;
}

CChunk CWorld::getChunkFromChunkCoords(jint chunkX, jint chunkZ, JNIEnv* env)
{
	return CChunk(env->CallObjectMethod(this->getInstance(), StrayCache::world_getChunkFromChunkCoords));
}

CIBlockState CWorld::getBlockState(BlockPos pos, JNIEnv* env) {
	return CIBlockState(env->CallObjectMethod(this->getInstance(), StrayCache::world_getBlockState, pos.getInstance()));
}

bool CWorld::isAirBlock(double x, double y, double z, JNIEnv* env)
{
	if (Base::version == FORGE_1_7_10)
	{
		return env->CallBooleanMethod(this->instance, StrayCache::world_isAirBlock, (int)x, (int)y, (int)z);
	}
	jclass blockPosClass = StrayCache::blockPos_class;
	jmethodID blockPosConstructor = env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	auto blockpos = BlockPos(env->NewObject(blockPosClass, blockPosConstructor, x, y, z));
	if (Base::version == FORGE_1_18_1)
	{
		auto blockstate = this->getBlockState(blockpos, env);
		return env->CallBooleanMethod(blockstate.getInstance(), StrayCache::blockStateBase_isAir);
	}
	return env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, blockpos.getInstance());
}

bool CWorld::isAirBlock(BlockPos pos, JNIEnv* env)
{
	if (Base::version == FORGE_1_18_1)
	{
		auto blockState = this->getBlockState(pos);
		return env->CallBooleanMethod(blockState.getInstance(), StrayCache::blockStateBase_isAir);
	}
	if (JNIHelper::IsForge()) {
		return env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());

	}
	return env->CallBooleanMethod(this->getInstance(), StrayCache::world_isAirBlock, pos.getInstance());
}



int CWorld::getBlock(double x, double y, double z, JNIEnv* env)
{
	if (this->getInstance() == NULL)return 0;
	if (Base::version == FORGE_1_7_10 || Base::version == LUNAR_1_12_2) {
		//TODO: Make this work for 1.7.10
		return 0;
	}
	jclass blockPosClass = StrayCache::blockPos_class;
	jmethodID blockPosConstructor = env->GetMethodID(blockPosClass, "<init>", "(DDD)V");
	jobject blockpos = env->NewObject(blockPosClass, blockPosConstructor, x, y, z);

	jboolean isAir = this->isAirBlock(blockpos);
	if (isAir) {
		env->DeleteLocalRef(blockpos);
		return 0;
	}

	const auto blockState = env->CallObjectMethod(this->getInstance(), StrayCache::world_getBlockState, blockpos);
	const auto block = env->CallObjectMethod(blockState, StrayCache::iBlockState_getBlock);
	int blockID = env->CallIntMethod(StrayCache::block_class, StrayCache::block_getIdFromBlock, block);

	//free memory
	env->DeleteGlobalRef(blockpos);
	env->DeleteLocalRef(blockState);
	env->DeleteLocalRef(block);

	return blockID;
}
