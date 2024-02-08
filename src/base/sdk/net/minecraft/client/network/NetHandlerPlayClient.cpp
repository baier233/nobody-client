#include "NetHandlerPlayClient.h"


CNetworkPlayerInfo CNetHandlerPlayClient::getPlayerInfo(Object UUID) {
	if (!this->check() || !UUID.check())
	{
		return NULL;
	}
	return CNetworkPlayerInfo(Java::Env->CallObjectMethod(this->getInstance(), StrayCache::netHandlerPlayClient_getPlayerInfo, UUID));
}