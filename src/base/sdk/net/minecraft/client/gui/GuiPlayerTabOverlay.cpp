#include "GuiPlayerTabOverlay.h"

String CGuiPlayerTabOverlay::getPlayName(CNetworkPlayerInfo info) {
	if (!(this->check() || info.check()))
	{
		return NULL;
	}
	return String(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::guiPlayerTabOverlay_getPlayerName, info.getInstance()));
}