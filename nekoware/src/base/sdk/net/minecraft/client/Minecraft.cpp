#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"
#include "../../../sdk.h"


CWorldClient CMinecraft::getTheWorld()
{
	if (!this->instance) return CWorldClient();
	return CWorldClient(Java::Env->GetObjectField(this->instance, StrayCache::minecraft_theWorld));
}

CEntityPlayerSP CMinecraft::getThePlayer()
{
	if (!this->instance) return CEntityPlayerSP();
	return CEntityPlayerSP(Java::Env->GetObjectField(this->instance, StrayCache::minecraft_thePlayer));
}

//GameSettings Minecraft::getGameSettings()
//{
//	if (!instance) return GameSettings();
//	return GameSettings(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["gameSettings"]));
//}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->getInstance(),StrayCache::minecraft_getRenderViewEntity));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->IsSameObject(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_currentScreen), NULL))
	{
		return false;
	}
	return true;
}

int CMinecraft::getDebugFPS()
{
	return Java::Env->CallIntMethod(this->getInstance(), StrayCache::minecraft_getDebugFPS);
}

void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::minecraft_clickMouse);

}

void CMinecraft::setRightClickDelayTimer(jint delay) {
	Java::Env->SetIntField(this->getInstance(), StrayCache::minecraft_rightClickDelayTimer, delay);
}

Object CMinecraft::getPlayerController()
{
	return Object(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_playerController));
}
CRenderManager CMinecraft::GetRenderManager() {
	if (!this->instance) return GetRenderManager();
	return CRenderManager(Java::Env->GetObjectField(SDK::Minecraft->getInstance(), StrayCache::minecraft_renderManager));
}

CNetHandlerPlayClient CMinecraft::getNetHandler()
{
	//return CNetHandlerPlayClient(Java::Env->CallObjectMethod(this->getInstance(),StrayCache::minecraft_getNetHandler));
	return CNetHandlerPlayClient(Java::Env->GetObjectField(thePlayer->getInstance(), StrayCache::entityPlayerSP_sendQueue));
}

CGuiIngame CMinecraft::getIngameGUI()
{
	auto objectGui = Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_ingameGUI);
	if (objectGui)
	{
		return CGuiIngame(objectGui);
	}
	return NULL;
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->getInstance(), StrayCache::minecraft_objectMouseOver));
}
