#pragma once
#include "../block/state/IBlockState.h"
#include "../../../Object.h"
#include "../entity/player/EntityPlayer.h"
#include "../../../../util/math/geometry.h"
#include "chunk/Chunk.h"
#include <vector>
#include "../block/state/BlockState.h"
#include "../util/BlockPos.h"
#include "../../../java/util/List.h"
#include "../util/BlockPos.h"
class CWorld : public Object
{
public:
	using Object::Object;
	List GetPlayerList(JNIEnv* env = Java::Env);
	List GetLoadedEntityList(JNIEnv* env = Java::Env);
	List GetLoadedTileEntityList(JNIEnv* env = Java::Env);
	CBlock GetBlock(int x, int y, int z, JNIEnv* env = Java::Env);

	Vector3 rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock, JNIEnv* env = Java::Env);

	CChunk getChunkFromChunkCoords(jint chunkX, jint chunkZ, JNIEnv* env = Java::Env);

	CIBlockState getBlockState(BlockPos pos, JNIEnv* env = Java::Env);

	bool isAirBlock(double x, double y, double z, JNIEnv* env = Java::Env);
	bool isAirBlock(BlockPos pos, JNIEnv* env = Java::Env);
	int getBlock(double x, double y, double z, JNIEnv* env = Java::Env);
};

