#pragma once
#include "../../commonData.h"

class Scaffold : public AbstractModule {
public:
	static Scaffold* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	BoolValue* TowerValue = new BoolValue("Tower", false);
private:
	Scaffold();
	float orYaw = 0;
	float orPitch = 0;
	float reverseYaw = 0;
};