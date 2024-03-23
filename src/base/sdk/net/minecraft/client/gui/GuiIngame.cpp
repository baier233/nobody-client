#include "GuiIngame.H"


CGuiPlayerTabOverlay CGuiIngame::getTabList(JNIEnv* env) {

	return CGuiPlayerTabOverlay(env->CallObjectMethod(this->getInstance(), StrayCache::GetInstance()->guiIngame_getTabList));
}