#include "BlockState.h"


CBlock CBlockState::getBlock(JNIEnv* env ) {
	if (!this->isValid() || this->isNULL())	return CBlock{};
	return CBlock(env->GetObjectField(this->instance, StrayCache::blockState_block));
}