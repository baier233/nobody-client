#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

float CGameSettings::GetFOV(JNIEnv* env )
{
	return env->GetFloatField(this->getInstance(), StrayCache::gamesettings_fovSetting);
}

void CGameSettings::SetGamma(float gamma, JNIEnv* env )
{
	env->SetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting, gamma);
}

float CGameSettings::GetGamma(JNIEnv* env )
{
	return env->GetFloatField(this->getInstance(), StrayCache::gamesettings_gammaSetting);
}

void CGameSettings::SetFullscreenKeyToNull(JNIEnv* env )
{

	env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 0);
}

void CGameSettings::RestoreFullscreenKey(JNIEnv* env )
{
	env->CallVoidMethod(this->getInstance(), StrayCache::gamesettings_setOptionKeyBinding, env->GetObjectField(this->getInstance(), StrayCache::gamesettings_keyBindFullscreen), 87);
}


int CGameSettings::GetThirdPersonView(JNIEnv* env )
{
	return env->GetIntField(this->getInstance(), StrayCache::gamesettings_thirdPersonView);
}

