#include "NetHandlerPlayClient.h"


CNetworkPlayerInfo CNetHandlerPlayClient::getPlayerInfo(Object UUID, JNIEnv* env) {
	if (!this->check() || !UUID.check())
	{
		return CNetworkPlayerInfo();
	}
	return CNetworkPlayerInfo(env->CallObjectMethod(this->getInstance(), StrayCache::netHandlerPlayClient_getPlayerInfo, UUID));
}