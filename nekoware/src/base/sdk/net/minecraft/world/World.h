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
	List GetPlayerList();

	Vector3 rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock);

	CChunk getChunkFromChunkCoords(jint chunkX, jint chunkZ);

	CIBlockState getBlockState(BlockPos pos);

	bool isAirBlock(double x, double y, double z);
	bool isAirBlock(BlockPos pos);
	int getBlock(double x, double y, double z);
};

