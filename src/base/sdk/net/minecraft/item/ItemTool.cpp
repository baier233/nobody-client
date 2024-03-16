#include "ItemTool.h"

float CItemTool::GetStrVsBlock(CItemStack stack, CBlock state, JNIEnv* env )
{
	return env->CallFloatMethod(this->instance, StrayCache::itemTool_getStrVsBlock, stack.getInstance(), state.getInstance());
}
