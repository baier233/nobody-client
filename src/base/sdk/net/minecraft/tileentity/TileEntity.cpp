#include "TileEntity.h"

BlockPos CTileEntity::getPos()
{
	if (!this->instance)return BlockPos();
	auto blockPos = Java::Env->CallObjectMethod(this->instance, StrayCache::tileEntity_getPos);
	if (!blockPos) return BlockPos{};
	return BlockPos(blockPos);
}
