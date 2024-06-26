#pragma once

#define LOLOLOL
#define LOLOLOL2

#include "../../ext/jni/jni.h"


#include "eventManager/events/EventKey.hpp"
#include <chrono>
#include <map>
#include <Windows.h>
enum Version
{
	FORGE_1_12_2,
	FORGE_1_8_9,
	FORGE_1_7_10,
	VANILLA_1_8_9,
	BADLION,
	LUNAR_1_8_9,
	LUNAR_1_12_2,
	FORGE_1_18_1,
	FPSMASTER_1_12_2,
	UNKNOWN
};



struct Base
{
	static void Init();
	static void initModule();
	static void checkVersion();
	static void handleEventKey(int key);
	static int InitUpdateMessge();
	static void Kill();
	static Version version;
	static void RenderLoop(HDC hdc);
	static inline bool Running;
	static inline bool justPressed;
	static inline std::string BuildVersion;
	static inline bool isObfuscate;
};

