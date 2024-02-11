#pragma once
#include "eventManager/events/EventKey.hpp"
#include <chrono>
#include "java/java.h"
enum Version
{
	FORGE_1_12_2,
	FORGE_1_8_9,
	FORGE_1_7_10,
	VANILLA_1_8_9,
	BADLION,//√ª≤‚ ‘
	LUNAR_1_8_9,
	UNKNOWN
};

struct Base
{
	static void Init();
	static void initConsole();
	static void initModule();
	static void checkVersion();
	static void handleEventKey(int key);
	static int InitUpdateMessge();
	static int InitHookNglClear();
	static void Kill();
	static Version version;
	static void RenderLoop(HDC hdc);
	static inline bool Running;
	static inline bool justPressed;
	static inline std::string BuildVersion;
	//1 = Lunar, 2 = Forge, 3 = Vanilla/Badlion
	static inline bool isObfuscate;
};


class Chronometer {
public:
	Chronometer(std::chrono::milliseconds everyXms);
	bool isElapsed();
	void setEvery(std::chrono::milliseconds everyXms);
	void reset();
private:
	std::chrono::steady_clock::time_point timerBegin;
	std::chrono::milliseconds targetMs;
};
