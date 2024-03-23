#include "Block.h"

int CBlock::GetID(JNIEnv* env )
{
	if (!this->getInstance())return 0;

	const auto blockClass = env->GetObjectClass(this->getInstance());

	const auto ret = env->CallStaticIntMethod(blockClass, StrayCache::GetInstance()->block_getIdFromBlock, this->getInstance());

	if (blockClass)
		env->DeleteLocalRef((jclass)blockClass);
	return ret;
}
