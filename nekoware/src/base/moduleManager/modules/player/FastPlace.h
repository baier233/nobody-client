#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>

class Fastplace :public AbstractModule {
public:
	static Fastplace* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	FloatValue* DelayValue = new FloatValue("Delay", 0, 0, 6);
private:
	Fastplace();
};