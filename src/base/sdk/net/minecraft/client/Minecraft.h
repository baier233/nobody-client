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
	CWorldClient getTheWorld(JNIEnv* env = Java::GetInstance()->Env);
	CEntityPlayerSP getThePlayer(JNIEnv* env = Java::GetInstance()->Env);
	CEntity GetRenderViewEntity(JNIEnv* env = Java::GetInstance()->Env);
	bool IsInGuiState(JNIEnv* env = Java::GetInstance()->Env);
	int getDebugFPS(JNIEnv* env = Java::GetInstance()->Env);
	void ClickMouse(JNIEnv* env = Java::GetInstance()->Env);
	void setRightClickDelayTimer(jint delay, JNIEnv* env = Java::GetInstance()->Env);
	Object getPlayerController(JNIEnv* env = Java::GetInstance()->Env);
	CMovingObjectPosition GetMouseOver(JNIEnv* env = Java::GetInstance()->Env);
	CRenderManager GetRenderManager(JNIEnv* env = Java::GetInstance()->Env);
	CNetHandlerPlayClient getNetHandler(JNIEnv* env = Java::GetInstance()->Env);
	CGuiIngame getIngameGUI(JNIEnv* env = Java::GetInstance()->Env);


	CEntityPlayerSP* thePlayer;
	CWorldClient* theWorld;
	CActiveRenderInfo* activeRenderInfo;
	CRenderManager* renderManager;
	//CNetHandlerPlayClient* netHandler;
	CTimer* timer;
	CGuiIngame* ingameGUI;
	CGameSettings* gameSettings;
};

