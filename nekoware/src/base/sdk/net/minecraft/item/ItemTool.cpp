#include "ItemTool.h"

float CItemTool::GetStrVsBlock(CItemStack stack, CBlock state)
{
	return Java::Env->CallFloatMethod(this->instance,StrayCache::itemTool_getStrVsBlock,stack.getInstance(),state.getInstance());
}
