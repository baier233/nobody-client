#pragma once

#include "../../../Object.h"

class CTimer : public Object
{
public:
	using Object::Object;

	float GetTimerSpeed(JNIEnv* env = Java::Env);

	void SetTimerSpeed(float speed, JNIEnv* env = Java::Env);

	float GetRenderPartialTicks(JNIEnv* env = Java::Env);
};

