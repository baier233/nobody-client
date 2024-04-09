#include "ItemTool.h"

float CItemTool::GetStrVsBlock(CItemStack stack, CBlock state, JNIEnv* env )
{
	return env->CallFloatMethod(this->instance, StrayCache::GetInstance()->itemTool_getStrVsBlock, stack.getInstance(), state.getInstance());
}
