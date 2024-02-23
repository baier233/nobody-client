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
#include <sys/timeb.h>
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
	typedef struct {
		double r;       // a fraction between 0 and 1
		double g;       // a fraction between 0 and 1
		double b;       // a fraction between 0 and 1
	} ColorRGB;

	typedef struct {
		double h;       // angle in degrees
		double s;       // a fraction between 0 and 1
		double v;       // a fraction between 0 and 1
	} ColorHSV;
	ColorHSV RGB2HSV(ColorRGB in);

	ColorRGB HSV2RGB(ColorHSV in);

	int rainbow(int delay, long timeOffset);
};

class EnabledListSorter {

public:
	bool operator()(HMOD m1, HMOD m2);
};