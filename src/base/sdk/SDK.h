#pragma once

#include "net/minecraft/client/Minecraft.h"
#include <map>
#include <memory>
class SDK;
std::map<DWORD, std::shared_ptr<SDK>>SDKMap{};


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

