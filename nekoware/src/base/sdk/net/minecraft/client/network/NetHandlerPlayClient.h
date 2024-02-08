#pragma once
#include "../../../../Object.h"
#include "NetworkPlayerInfo.h"
class CNetHandlerPlayClient : public Object
{
public:
	using Object::Object;
	CNetworkPlayerInfo getPlayerInfo(Object UUID);
};