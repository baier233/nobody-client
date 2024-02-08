#pragma once
#include "../../../../Object.h"
#include "../../../../java/lang/String.h"
#include "../network/NetworkPlayerInfo.h"
class CGuiPlayerTabOverlay : public Object
{
public:
	using Object::Object;
	String getPlayName(CNetworkPlayerInfo info);
};