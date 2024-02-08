#pragma once
#include "../../commonData.h"

class Killaura : public AbstractModule
{
public:
	static Killaura* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();

	FloatValue* rangeValue = new FloatValue("Range", 3.5f, 3.0f, 5.0f);
	FloatValue* leftMinCpsValue = new FloatValue("Min CPS", 8.0f, 1.0f, 20.0f);
	FloatValue* leftMaxCpsValue = new FloatValue("Max CPS", 14.0f, 1.0f, 20.0f);
	FloatValue* fovValue = new FloatValue("Fov", 360.0f, 0.f, 360.0f);

	BoolValue* keepSprintValue = new BoolValue("KeepSprint", false);
	BoolValue* autoblockValue = new BoolValue("AutoBlock", false);

	ModeValue* killauraMode = new ModeValue("Mode", { Legit,Normal }, modes, Legit);
	ModeValue* targetPriorityListMode = new ModeValue("Target", { Distance,Health,Crosshair }, targetPriorityList, Distance);
	
private:

	bool pitchInfluenced = false;
	Vector3 data;
	CEntityPlayer player;
	enum KILLAURAMODE {
		Legit,
		Normal
	};

	enum TARGETVALUES {
		Distance,
		Health,
		Crosshair
	};
	const char* modes[3]{ "Legit", "Normal", "Silent" };
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
	Killaura();
};