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
	CWorldClient getTheWorld(JNIEnv* env = Java::Env);
	CEntityPlayerSP getThePlayer(JNIEnv* env = Java::Env);
	CEntity GetRenderViewEntity(JNIEnv* env = Java::Env);
	bool IsInGuiState(JNIEnv* env = Java::Env);
	int getDebugFPS(JNIEnv* env = Java::Env);
	void ClickMouse(JNIEnv* env = Java::Env);
	void setRightClickDelayTimer(jint delay, JNIEnv* env = Java::Env);
	Object getPlayerController(JNIEnv* env = Java::Env);
	CMovingObjectPosition GetMouseOver(JNIEnv* env = Java::Env);
	CRenderManager GetRenderManager(JNIEnv* env = Java::Env);
	CNetHandlerPlayClient getNetHandler(JNIEnv* env = Java::Env);
	CGuiIngame getIngameGUI(JNIEnv* env = Java::Env);


	CEntityPlayerSP* thePlayer;
	CWorldClient* theWorld;
	CActiveRenderInfo* activeRenderInfo;
	CRenderManager* renderManager;
	//CNetHandlerPlayClient* netHandler;
	CTimer* timer;
	CGuiIngame* ingameGUI;
	CGameSettings* gameSettings;
};

