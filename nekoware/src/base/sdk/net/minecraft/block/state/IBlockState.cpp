#include "IBlockState.h"

CBlock CIBlockState::getBlock(JNIEnv* env )
{
	return CBlock(env->CallObjectMethod(this->instance, StrayCache::iBlockState_getBlock));
}
