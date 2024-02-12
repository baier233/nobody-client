#include "sdk.h"
#include "../util/logger.h"
#include "../java/java.h"
#include "strayCache.h"
#include "Object.h"

void SDK::Init()
{
	StrayCache::Initialize();
	SDK::Minecraft = new CMinecraft(Java::Env->CallStaticObjectMethod(StrayCache::minecraft_class, StrayCache::minecraft_getMinecraft));
	SDK::Minecraft->activeRenderInfo = new CActiveRenderInfo();
	SDK::Minecraft->theWorld = new CWorldClient(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_theWorld));
	SDK::Minecraft->thePlayer = new CEntityPlayerSP(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_thePlayer));
	SDK::Minecraft->renderManager = new CRenderManager(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_renderManager));
	SDK::Minecraft->gameSettings = new CGameSettings(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_gameSettings));
	////SDK::Minecraft->ingameGUI = new CGuiIngame(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_ingameGUI));
	SDK::Minecraft->timer = new CTimer(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_timer));
}

void SDK::Clean() 
{

	delete Minecraft;
}