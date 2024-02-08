#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>


class Reach :public AbstractModule {
public:
	static Reach* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	FloatValue* ReachDistanceValue = new FloatValue("Reach Distance", .5f, 0.f, 3.f);
private:
	Reach();
};