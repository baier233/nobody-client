#pragma once

#include "../../../Object.h"
#include "../client/entity/EntityPlayerSP.h"
#include "multiplayer/WorldClient.h"
#include "renderer/ActiveRenderInfo.h"
#include "renderer/entity/RenderManager.h"
#include "../util/Timer.h"
#include "settings/GameSettings.h"
#include "../util/MovingObjectPosition.h"
#include "network/NetHandlerPlayClient.h"
#include "gui/GuiIngame.h"
class CMinecraft : public Object
{
public:
	using Object::Object;
	CWorldClient getTheWorld();
	CEntityPlayerSP getThePlayer();
	CEntity GetRenderViewEntity();
	bool IsInGuiState();
	int getDebugFPS();
	void ClickMouse();
	void setRightClickDelayTimer(jint delay);
	Object getPlayerController();
	CMovingObjectPosition GetMouseOver();
	CRenderManager GetRenderManager();
	CNetHandlerPlayClient getNetHandler();
	CGuiIngame getIngameGUI();


	CEntityPlayerSP* thePlayer;
	CWorldClient* theWorld;
	CActiveRenderInfo* activeRenderInfo;
	CRenderManager* renderManager;
	//CNetHandlerPlayClient* netHandler;
	CTimer* timer;
	CGuiIngame* ingameGUI;
	CGameSettings* gameSettings;
};

