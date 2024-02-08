#pragma once
#include "../../../util/math/geometry.h"
#include "../../../util/type/ArrayList.h"
#include <string>
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include <iostream>
#include "../../../sdk/net/minecraft/client/network/NetHandlerPlayClient.h"
#include "../../../sdk/net/minecraft/client/network/NetworkPlayerInfo.h"
#include "../../../sdk/net/minecraft/client/gui/GuiPlayerTabOverlay.h"
#include "../../../sdk/net/minecraft/client/gui/GuiInGame.h"
#include "../../../sdk/java/lang/String.h"
class Antibot :public AbstractModule {
public:
	static Antibot* getInstance();
	void onEnable();
	void onDisable();
	bool isBot(CEntityPlayer p) {
		if (Java::Env->IsSameObject(p.getInstance(), NULL)) {
			return true;
		}

		float height = p.GetHeight();

		if (height <= 0.5f)
		{
			heightBots.add(p);
		}
		else {
			heightBots.remove(p);
		}

		if (p.isPlayerSleeping())
		{
			sleepingEntities.add(p);
		}
		else {
			sleepingEntities.remove(p);
		}

		if (p.GetHealth() <= 0)
		{
			healthEntities.add(p);
		}
		else {
			healthEntities.remove(p);
		}
		
		return healthEntities.contains(p) || heightBots.contains(p) || sleepingEntities.contains(p);

	}
	void RenderMenu();
private:
	std::vector<CEntityPlayer> bots;
	Antibot();
	CMinecraft* mc;
	CGuiPlayerTabOverlay tablist;
	ArrayList<CEntityPlayer> heightBots;
	ArrayList<CEntityPlayer> infoBots;
	CNetworkPlayerInfo playerinfo;
	CNetHandlerPlayClient nethandler;
	ArrayList<String> tempNameBots;
	ArrayList<CEntityPlayer> sleepingEntities;
	ArrayList<CEntityPlayer> healthEntities;
};