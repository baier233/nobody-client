#pragma once

#include "../../../Object.h"

class CTimer : public Object
{
public:
	using Object::Object;

	float GetTimerSpeed(JNIEnv* env = Java::GetInstance()->Env);

	void SetTimerSpeed(float speed, JNIEnv* env = Java::GetInstance()->Env);

	float GetRenderPartialTicks(JNIEnv* env = Java::GetInstance()->Env);
};

