#include "Block.h"

int CBlock::GetID()
{
	if(!this->getInstance())return 0;

	const auto blockClass = Java::Env->GetObjectClass(this->getInstance());

	const auto ret = Java::Env->CallStaticIntMethod(blockClass,StrayCache::block_getIdFromBlock,this->getInstance());

	if (blockClass)
		Java::Env->DeleteLocalRef((jclass)blockClass);
	return ret;
}
