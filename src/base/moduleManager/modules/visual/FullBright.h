#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>
#include "../../commonData.h"


class Fulbright :public AbstractModule {
public:
	static Fulbright* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
private:
	Fulbright();
	int currentGamma;
};