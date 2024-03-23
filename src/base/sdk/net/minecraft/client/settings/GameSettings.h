#pragma once
#include "../../../../Object.h"

class CGameSettings : public Object
{
public:
	using Object::Object;
	int GetThirdPersonView(JNIEnv* env = Java::GetInstance()->Env);
	float GetFOV(JNIEnv* env = Java::GetInstance()->Env);
	void SetGamma(float gamma, JNIEnv* env = Java::GetInstance()->Env);
	float GetGamma(JNIEnv* env = Java::GetInstance()->Env);
	void SetFullscreenKeyToNull(JNIEnv* env = Java::GetInstance()->Env);
	void RestoreFullscreenKey(JNIEnv* env = Java::GetInstance()->Env);
};

