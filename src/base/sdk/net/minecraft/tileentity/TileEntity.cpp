#include "TileEntity.h"

BlockPos CTileEntity::getPos()
{
	if (!this->instance)return BlockPos();
	auto blockPos = Java::GetInstance()->Env->CallObjectMethod(this->instance, StrayCache::GetInstance()->tileEntity_getPos);
	if (!blockPos) return BlockPos{};
	return BlockPos(blockPos);
}
