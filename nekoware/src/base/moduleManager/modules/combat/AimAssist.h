#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"

class AimAssist :public AbstractModule {
public:
	static AimAssist* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderUpdate();
	void RenderMenu();


	FloatValue* FovValue = new FloatValue("Fov", 35.0f,	 1, 360);
	FloatValue* AimDistanceValue = new FloatValue("Aim Distance", 4.f, 1.0f, 8.0f);
	FloatValue* SmoothValue = new FloatValue("Smooth", 15.f, 1.0f, 90.0f);
	FloatValue* AdaptiveOffsetValue = new FloatValue("Adaptive Offset", 3, 0.1f, 15.f);
	FloatValue* RandomYawValue = new FloatValue("RandomYaw Offset", 2, 0.0f, 10.0f);
	FloatValue* RandomPitchValue = new FloatValue("RandomPitch Offset", .075f, 0.0f, 1.0f);
	BoolValue* VisibilityCheckValue = new BoolValue("VisibilityCheck", true);
	BoolValue* AimKeyValue = new BoolValue("AimKey", true);
	BoolValue* AdaptiveValue = new BoolValue("Adaptive", true);
	BoolValue* AimAssistFeedbackValue = new BoolValue("AimAssistFeedback", true);
	BoolValue* FovCircleValue = new BoolValue("FovCircle", true);
	ModeValue* TargetPriorityValue = new ModeValue("TargetPriority", { Distance , Health , Crosshair }, targetPriorityList, Crosshair);

	
private:
	Vector3 data;
	Vector3 renderData;
	bool pitchInfluenced = false;

	enum TARGETMODE {
		Distance,
		Health,
		Crosshair
	};
	const char* targetPriorityList[3]{ "Distance", "Health", "Closest to Crosshair" };
	AimAssist();
};