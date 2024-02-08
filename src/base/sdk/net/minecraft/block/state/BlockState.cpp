#include "BlockState.h"


CBlock CBlockState::getBlock() {
	if (!this->isValid() || this->isNULL())	return CBlock{};
	return CBlock(Java::Env->GetObjectField(this->instance, StrayCache::blockState_block));
}