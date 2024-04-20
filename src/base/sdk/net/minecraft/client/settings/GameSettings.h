#pragma once
#include "../../../../Object.h"

class CGameSettings : public Object
{
public:
	using Object::Object;
	int GetThirdPersonView(JNIEnv* env = Java::Env);
	float GetFOV(JNIEnv* env = Java::Env);
	void SetGamma(float gamma, JNIEnv* env = Java::Env);
	float GetGamma(JNIEnv* env = Java::Env);
	void SetFullscreenKeyToNull(JNIEnv* env = Java::Env);
	void RestoreFullscreenKey(JNIEnv* env = Java::Env);
};

