#include "GuiIngame.H"


CGuiPlayerTabOverlay CGuiIngame::getTabList() {
	
	return CGuiPlayerTabOverlay(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::guiIngame_getTabList));
}