#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <Windows.h>

#include <string>
#include <vector>
//struct Blink
//{
//	inline static ULONGLONG timer;
//	inline static bool running;
//	inline static bool wasActive;
//	inline static int bind = 'H';
//	inline static float Milliseonds = 10;
//
//	inline static bool Enabled = false;
//	//inline static bool throttle = false;
//
//	static void Update();
//
//	static void RenderMenu();
//	static void OnReceiveData();
//};

class Blink :public AbstractModule {
public:
	static Blink* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	void OnReceiveData();

	ULONGLONG timer;
	bool running;
	bool wasActive;
	float Milliseonds = 10;
private:
	Blink();
};