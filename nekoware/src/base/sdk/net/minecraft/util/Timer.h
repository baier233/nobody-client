#pragma once

#include "../../../Object.h"

class CTimer : public Object
{
public:
	using Object::Object;

	float GetTimerSpeed();

	void SetTimerSpeed(float speed);

	float GetRenderPartialTicks();
};

