#pragma once
#include "../../AbstractModule.h"
#include <vector>
#include "../../ModuleManager.h"
#include <algorithm>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../util/utils.h"
#include <chrono>
#include <cmath>
#include <cstdint>

struct Color {
	float red;
	float green;
	float blue;
	float alpha;
};


class HUD :public AbstractModule {
public:
	static HUD* getInstance();
	void onEnable();
	void onDisable();
	void RenderUpdate();
	void RenderMenu();

	ModeValue* ArrayListMode = new ModeValue("Arraylist", { New ,Old }, Arraylists, New);
private:
	HUD();
	std::vector<HMOD> enabledMods;
	enum Arraylist {
		New,
		Old
	};
	const char* Arraylists[3]{ "New", "Old" };

	Color HSBtoRGB(float hue, float saturation, float brightness);

	Color rainbow(float tick);
};

class EnabledListSorter {

public:
	bool operator()(HMOD m1, HMOD m2);
};