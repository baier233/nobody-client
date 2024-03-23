#include "sdk.h"
#include "../util/logger.h"
#include "../java/java.h"
#include "strayCache.h"
#include "Object.h"

void SDK::Init()
{
	if (this->Minecraft) return;
	StrayCache::GetInstance()->Initialize();
	SDK::Minecraft = new CMinecraft(Java::GetInstance()->Env->CallStaticObjectMethod(StrayCache::GetInstance()->minecraft_class, StrayCache::GetInstance()->minecraft_getMinecraft));
	SDK::GetInstance()->Minecraft->activeRenderInfo = new CActiveRenderInfo();
	SDK::GetInstance()->Minecraft->theWorld = new CWorldClient(Java::GetInstance()->Env->GetObjectField(SDK::GetInstance()->Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_theWorld));
	SDK::GetInstance()->Minecraft->thePlayer = new CEntityPlayerSP(Java::GetInstance()->Env->GetObjectField(SDK::GetInstance()->Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_thePlayer));

	if (Base::version == FORGE_1_7_10)
	{
		SDK::GetInstance()->Minecraft->renderManager = new CRenderManager(Java::GetInstance()->Env->GetStaticObjectField(StrayCache::GetInstance()->renderManager_class, StrayCache::GetInstance()->renderManager_Instance));
	}
	else if (Base::version != FORGE_1_18_1)
	{
		SDK::GetInstance()->Minecraft->renderManager = new CRenderManager(Java::GetInstance()->Env->GetObjectField(SDK::GetInstance()->Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_renderManager));
	}
	SDK::GetInstance()->Minecraft->gameSettings = new CGameSettings(Java::GetInstance()->Env->GetObjectField(Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_gameSettings));
	////SDK::GetInstance()->Minecraft->ingameGUI = new CGuiIngame(Java::GetInstance()->Env->GetObjectField(Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_ingameGUI));
	SDK::GetInstance()->Minecraft->timer = new CTimer(Java::GetInstance()->Env->GetObjectField(Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_timer));
}

void SDK::Clean()
{

	delete Minecraft;
}