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
	SDK::Minecraft->thePlayer = new CEntityPlayerSP(Java::Env->GetObjectField(StrayCache::minecraft_class, StrayCache::minecraft_thePlayer));
	SDK::Minecraft->renderManager = new CRenderManager(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_renderManager));
	SDK::Minecraft->gameSettings = new CGameSettings(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_gameSettings));
	//std::cout << Minecraft->thePlayer->getInstance() << std::endl;
	/*if (Minecraft->thePlayer->getInstance() != nullptr)
	{
		SDK::Minecraft->netHandler = new CNetHandlerPlayClient(Java::Env->GetObjectField(Minecraft->thePlayer->getInstance(), StrayCache::entityPlayerSP_sendQueue));
	}
	else {
		SDK::Minecraft->netHandler == new CNetHandlerPlayClient();
	}*/
	
	//std::cout << Minecraft->netHandler->getInstance() << " " << StrayCache::minecraft_netManager  << std::endl;
	SDK::Minecraft->ingameGUI = new CGuiIngame(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_ingameGUI));
	SDK::Minecraft->timer = new CTimer(Java::Env->GetObjectField(Minecraft->getInstance(), StrayCache::minecraft_timer));

}

void SDK::Clean() 
{

	delete Minecraft;
}