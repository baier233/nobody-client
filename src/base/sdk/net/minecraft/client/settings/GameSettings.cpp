#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

float CGameSettings::GetFOV(JNIEnv* env )
{
	return env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->gamesettings_fovSetting);
}

void CGameSettings::SetGamma(float gamma, JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		env->SetDoubleField(this->getInstance(), StrayCache::GetInstance()->gamesettings_gammaSetting, 
			(double)gamma);
		return;
	}
	env->SetFloatField(this->getInstance(), StrayCache::GetInstance()->gamesettings_gammaSetting, gamma);
}

float CGameSettings::GetGamma(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		env->GetDoubleField(this->getInstance(), StrayCache::GetInstance()->gamesettings_gammaSetting);
		return 0.f;
	}
	return env->GetFloatField(this->getInstance(), StrayCache::GetInstance()->gamesettings_gammaSetting);
}

void CGameSettings::SetFullscreenKeyToNull(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		return;
	}
	env->CallVoidMethod(this->getInstance(), StrayCache::GetInstance()->gamesettings_setOptionKeyBinding, env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->gamesettings_keyBindFullscreen), 0);
}

void CGameSettings::RestoreFullscreenKey(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		return;
	}
	env->CallVoidMethod(this->getInstance(), StrayCache::GetInstance()->gamesettings_setOptionKeyBinding, env->GetObjectField(this->getInstance(), StrayCache::GetInstance()->gamesettings_keyBindFullscreen), 87);
}


int CGameSettings::GetThirdPersonView(JNIEnv* env )
{
	if (Base::version == FORGE_1_18_1)
	{
		auto cameraType = Java::GetInstance()->Env->GetObjectField(SDK::Minecraft->gameSettings->getInstance(),StrayCache::GetInstance()->gamesettings_cameraType);
		if (!cameraType) return 0;
		bool isFirstPerson = Java::GetInstance()->Env->CallBooleanMethod(cameraType, StrayCache::GetInstance()->cameraType_isFirstPerson);
		if (isFirstPerson)
		{
			return 0;
		}
		else {
			return 2;
		}
		
		
	}
	return env->GetIntField(this->getInstance(), StrayCache::GetInstance()->gamesettings_thirdPersonView);
}

