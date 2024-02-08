#pragma once
#include "../../../../Object.h"

class CGameSettings : public Object
{
public:
	using Object::Object;
	int GetThirdPersonView();
	float GetFOV();
	void SetGamma(float gamma);
	float GetGamma();
	void SetFullscreenKeyToNull();
	void RestoreFullscreenKey();
};

