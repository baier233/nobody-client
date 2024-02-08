#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

float CGameSettings::GetFOV()
{
	return Java::Env->GetFloatField(this->getInstance() , StrayCache::gamesettings_fovSetting);
}

void CGameSettings::SetGamma(float gamma)
{
	jobject instance = this->getInstance();
	Java::Env->SetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting, gamma);
}

float CGameSettings::GetGamma()
{
	return Java::Env->GetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting);
}

void CGameSettings::SetFullscreenKeyToNull()
{

	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, Java::Env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	Java::Env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, Java::Env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 87);
}


int CGameSettings::GetThirdPersonView()
{
	return Java::Env->GetIntField(this->getInstance(), StrayCache::gamesettings_thirdPersonView);
}

