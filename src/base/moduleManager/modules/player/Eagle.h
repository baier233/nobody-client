#pragma once
#pragma once
#include "../../../util/math/geometry.h"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../AbstractModule.h"
#include <string>
#include <vector>

//struct Eagle : public module
//{
//	inline static int bind = 'Y';
//
//	inline static bool Enabled = false;
//
//	static void Update();
//
//	static void RenderMenu();
//};

class Eagle :public AbstractModule {
public:
	static Eagle* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
private:
	Eagle();
};