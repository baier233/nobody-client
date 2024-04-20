#include "BlockState.h"


CBlock CBlockState::getBlock(JNIEnv* env ) {
	if (!this->isValid() || this->isNULL())	return CBlock{};
	if (Base::version == FORGE_1_18_1)
	{
		return CBlock(env->CallObjectMethod(this->instance, StrayCache::blockStateBase_getBlock));
	}

	return CBlock(env->GetObjectField(this->instance, StrayCache::blockState_block));
}

