#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"
#include "../../../sdk.h"


CWorldClient CMinecraft::getTheWorld(JNIEnv* env)
{
	if (!this->instance) return CWorldClient();
	return CWorldClient(env->GetObjectField(this->instance, StrayCache::GetInstance()->minecraft_theWorld));
}

CEntityPlayerSP CMinecraft::getThePlayer(JNIEnv* env)
{
	if (!this->instance) return CEntityPlayerSP();
	return CEntityPlayerSP(env->GetObjectField(this->instance, StrayCache::GetInstance()->minecraft_thePlayer));
}

//GameSettings Minecraft::getGameSettings()
//{
//	if (!instance) return GameSettings();
//	return GameSettings(Ripterms::p_env->GetObjectField(instance, Ripterms::classcache->MinecraftClass.fields["gameSettings"]));
//}

CEntity CMinecraft::GetRenderViewEntity(JNIEnv* env)
{
	return CEntity(env->CallObjectMethod(this->getInstance(), StrayCache::GetInstance()->minecraft_getRenderViewEntity));
}

bool CMinecraft::IsInGuiState(JNIEnv* env)
{
	if (env->IsSameObject(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->minecraft_currentScreen), NULL))
	{
		return false;
	}
	return true;
}

int CMinecraft::getDebugFPS(JNIEnv* env)
{
	return env->CallIntMethod(this->getInstance(), StrayCache::GetInstance()->minecraft_getDebugFPS);
}

void CMinecraft::ClickMouse(JNIEnv* env)
{
	env->CallVoidMethod(this->getInstance(), StrayCache::GetInstance()->minecraft_clickMouse);

}

void CMinecraft::setRightClickDelayTimer(jint delay, JNIEnv* env) {
	env->SetIntField(this->getInstance(), StrayCache::GetInstance()->minecraft_rightClickDelayTimer, delay);
}

Object CMinecraft::getPlayerController(JNIEnv* env)
{
	return Object(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->minecraft_playerController));
}
CRenderManager CMinecraft::GetRenderManager(JNIEnv* env) {
	if (!this->instance) return GetRenderManager();
	return CRenderManager(env->GetObjectField(SDK::GetInstance()->Minecraft->getInstance(), StrayCache::GetInstance()->minecraft_renderManager));
}

CNetHandlerPlayClient CMinecraft::getNetHandler(JNIEnv* env)
{
	//return CNetHandlerPlayClient(env->CallObjectMethod(this->getInstance(),StrayCache::GetInstance()->minecraft_getNetHandler));
	return CNetHandlerPlayClient(env->GetObjectField(thePlayer->getInstance(), StrayCache::GetInstance()->entityPlayerSP_sendQueue));
}

CGuiIngame CMinecraft::getIngameGUI(JNIEnv* env)
{
	auto objectGui = env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->minecraft_ingameGUI);
	if (objectGui)
	{
		return CGuiIngame(objectGui);
	}
	return CGuiIngame();
}

CMovingObjectPosition CMinecraft::GetMouseOver(JNIEnv* env)
{
	return CMovingObjectPosition(env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->minecraft_objectMouseOver));
}
