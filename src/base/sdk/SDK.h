#pragma once

#include "net/minecraft/client/Minecraft.h"

class SDK
{
public:
	static SDK* GetInstance() {

		  
	}
	static inline CMinecraft* Minecraft;
	static void Init();
	static void Clean();
};

