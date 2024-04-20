#pragma once

#include "net/minecraft/client/Minecraft.h"


class SDK
{
public:
	static inline CMinecraft* Minecraft;
	static void Init();
	static void Clean();
};
