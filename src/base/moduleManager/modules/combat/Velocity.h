#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"


#include <string>
#include <vector>


class Velocity :public AbstractModule {
public:
	static Velocity* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	FloatValue* HorizontalValue = new FloatValue("Horizontal", 0.f, 0, 1.f);
	FloatValue* VerticalValue = new FloatValue("Vertical", 1.f, 0, 1.f);
	BoolValue* OnlyTargetingValue = new BoolValue("Only Targeting", false);
	ModeValue* VelocityModeValue = new ModeValue("Mode", {Normal,Intave,Push,Strafe},modes,Normal);
	
private:
	enum VELOCITYMODE {
		Normal,
		Intave,
		Push,
		Strafe
	};
	const char* modes[4]{ "Normal", "Intave", "Push", "Strafe" };
	Velocity();
};