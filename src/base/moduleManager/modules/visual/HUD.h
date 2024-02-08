#pragma once
#include "../../AbstractModule.h"
#include <vector>
#include "../../ModuleManager.h"
#include <algorithm>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../util/utils.h"
class HUD :public AbstractModule {
public:
	static HUD* getInstance();
	void onEnable();
	void onDisable(); 
	void RenderUpdate();
	void RenderMenu();
private:
	HUD();
	std::vector<HMOD> enabledMods;
	struct Block {
		float x;
		float y;
		float width;
		float height;
	};
};

class EnabledListSorter {

public:
	bool operator()(HMOD m1, HMOD m2);
};