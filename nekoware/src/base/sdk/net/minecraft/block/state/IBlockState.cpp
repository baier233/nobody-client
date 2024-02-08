#include "IBlockState.h"

CBlock CIBlockState::getBlock()
{
	return CBlock(Java::Env->CallObjectMethod(this->instance, StrayCache::iBlockState_getBlock));
}
