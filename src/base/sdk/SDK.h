#pragma once

#include "net/minecraft/client/Minecraft.h"
#include <map>
#include <memory>


class SDK
{
public:
	static SDK* GetInstance() {
		static auto shared = std::make_shared<SDK>();
		return shared.get();
		  
	}
	CMinecraft* Minecraft;
	void Init();
	void Clean();
};

