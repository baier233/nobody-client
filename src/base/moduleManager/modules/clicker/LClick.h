#pragma once
#include "../../AbstractModule.h"
#include "../../../eventManager/events/EventUpdate.hpp"
//struct LClick
//{
//	inline static int bind = 0;
//
//	inline static bool Enabled = false;
//
//	inline static float leftMaxCps = 14;
//	inline static float leftMinCps = 8;
//	inline static bool ignoreBlocks = true;
//	inline static bool blockhit = false;
//	inline static float blockHitChance = 3.f;
//	inline static bool inInventory = false;
//
//	static void Update();
//	static void RenderMenu();
//};

class LClick :public AbstractModule {
public:
	static LClick* getInstance();
	void onEnable();
	void onDisable();
	void onUpdate(const EventUpdate e);
	void RenderMenu();
	FloatValue* leftMaxCpsValue = new FloatValue("Max CPS", 14, 0, 20);
	FloatValue* leftMinCpsValue = new FloatValue("Min CPS", 8, 0, 20);
	FloatValue* blockHitChanceValue = new FloatValue("BlockHitChance", 3, 1, 50);
	BoolValue* ignoreBlocksValue = new BoolValue("Ignore Block", true);
	BoolValue* blockHitValue = new BoolValue("BlockHit", false);
	BoolValue* inInventoryValue = new BoolValue("In Inventory", false);
	

private:
	LClick();
};