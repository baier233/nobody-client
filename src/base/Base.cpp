#include "base.h"

#include "../main.h"
#include "util/logger.h"
#include "menu/menu.h"
#include "moduleManager/ModuleManager.h"
#include "sdk/sdk.h"
#include "util/window/borderless.h"
#include <thread>
#include <unordered_map>
#include "security/security.hpp"
#include "eventManager/events/EventKey.hpp"

#include "../../ext/minhook/minhook.h"

#include "moduleManager/modules/clicker/LClick.h"
#include "moduleManager/modules/clicker/RClick.h"

#include "moduleManager/modules/combat/killaura.h"
#include "moduleManager/modules/combat/aimAssist.h"
#include "moduleManager/modules/combat/antibot.h"
#include "moduleManager/modules/combat/teams.h"
#include "moduleManager/modules/combat/reach.h"
#include "moduleManager/modules/combat/velocity.h"

#include "moduleManager/modules/player/Scaffold.h"
#include "moduleManager/modules/player/blink.h"
#include "moduleManager/modules/player/autotool.h"
#include "moduleManager/modules/player/eagle.h"
#include "moduleManager/modules/player/fastplace.h"

#include "moduleManager/modules/visual/Xray.h"
#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/visual/HUD.h"
#include "moduleManager/modules/visual/fullbright.h"

#include "Resource/ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "util/stb_image.h"
#include "menu/Notification/NotificationManager.h"
#include "menu/web/WebServerManager.h"

Version Base::version = UNKNOWN;

// LUA import
//#include "extension/scripting.hpp"

const char* GetWindowTitle(HWND hWnd)
{
	char windowTitle[128];
	GetWindowTextA(hWnd, windowTitle, 128);

	return windowTitle;
}

bool IsKeyReleased(int key)
{
	static std::unordered_map<int, bool> keyStates;

	bool currentState = (GetAsyncKeyState(key) & 0x8000) == 0;
	bool prevState = keyStates[key];
	keyStates[key] = currentState;

	return prevState && !currentState;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void handleUpdate(JNIEnv* env)
{
	MSG msg;
	while (PeekMessage(
		&msg,     // message information
		NULL,     // handle to window
		0,        // first message
		0,        // last message
		PM_REMOVE // removal options
	))
	{
		if (msg.message == WM_QUIT)
			break;
		if (msg.message == WM_KEYDOWN)
		{
			Base::justPressed = true;
			if (msg.wParam == Menu::Keybind)
				Menu::Open = !Menu::Open;
			if (msg.wParam == VK_ESCAPE && Menu::Open)
				Menu::Open = false;
			ModuleManager::getInstance().ProcessKeyEvent(msg.wParam);
			//EventManager::getInstance().call(EventKey(msg.wParam));
		}

		/*UINT value1 = msg.message;
		UINT value2 = msg.wParam;
		UINT value3 = msg.lParam;
		*/

		TranslateMessage(&msg); // ·¢³öWM_CHAR

		//(jint)value1, (jlong)value2, (jlong)value3);

		DispatchMessage(&msg);
	}
}

int Base::InitUpdateMessge() {
	JNINativeMethod native[] = {
	{const_cast<char*>("nUpdate"), const_cast<char*>("()V"), (void*)(handleUpdate)} };
	jclass clazz{};
	Java::AssignClass("org.lwjgl.opengl.WindowsDisplay", clazz);
	if (!clazz)
	{
		Java::Env->FindClass("org/lwjgl/opengl/WindowsDisplay");
	}
	if (!clazz)
	{
		std::cout << "Unable to find windowsDisplay Class" << std::endl;
		return -1;
	}

	return Java::Env->RegisterNatives(clazz, native, sizeof(native) / sizeof(JNINativeMethod));
}
#include<Windows.h>
#include "moduleManager/modules/visual/ChestESP.h"
#include "moduleManager/modules/visual/BlockESP.h"
#include "moduleManager/modules/visual/Chams.h"
void Base::Init()
{
	MH_Initialize();
	BuildVersion = "Build 20240207 - f563a08";//动态获取？
	Java::Init();
	Base::isObfuscate = false;
	checkVersion();
	SDK::Init();
	Menu::Init();
	initModule();
	InitUpdateMessge();
	ResourceManager::getInstance().LoadAllResource();
	Base::Running = true;
	SDK::Minecraft->gameSettings->SetFullscreenKeyToNull();
	WebServerManager::getInstance().Start(8080);
	NotificationManager::getInstance().makeNotification("Press INSERT to open Gui", Type::INFO);

	while (Base::Running)
	{
		if (IsKeyReleased(VK_F11)) {
			if (Borderless::Enabled)
				Borderless::Restore(Menu::HandleWindow);
			else
				Borderless::Enable(Menu::HandleWindow);
		}

		EventManager::getInstance().call(EventUpdate());

#ifndef _DEBUG
		/*HideFromDebugger();*/
#endif

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

#ifndef _DEBUG
		/*Check();*/
#endif
	}

	Main::Kill();
}
void Base::initConsole() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

void Base::initModule() {
	
	{
		ModuleManager::getInstance().addModule<Killaura>(Killaura::getInstance());
		ModuleManager::getInstance().addModule<AimAssist>(AimAssist::getInstance());
		ModuleManager::getInstance().addModule<Reach>(Reach::getInstance());
		ModuleManager::getInstance().addModule<Velocity>(Velocity::getInstance());
		ModuleManager::getInstance().addModule<Antibot>(Antibot::getInstance());
		ModuleManager::getInstance().addModule<Teams>(Teams::getInstance());
	}


	{
		ModuleManager::getInstance().addModule<LClick>(LClick::getInstance());
		ModuleManager::getInstance().addModule<RClick>(RClick::getInstance());
	}


	{
		ModuleManager::getInstance().addModule<Eagle>(Eagle::getInstance());
		ModuleManager::getInstance().addModule<Fastplace>(Fastplace::getInstance());
		ModuleManager::getInstance().addModule<AutoTool>(AutoTool::getInstance());
		ModuleManager::getInstance().addModule<Blink>(Blink::getInstance());
	}

	{
		ModuleManager::getInstance().addModule<Esp>(Esp::getInstance());
		ModuleManager::getInstance().addModule<Fulbright>(Fulbright::getInstance());
		ModuleManager::getInstance().addModule<Xray>(Xray::getInstance());
		ModuleManager::getInstance().addModule<HUD>(HUD::getInstance());
		ModuleManager::getInstance().addModule<Chams>(Chams::getInstance());
		ModuleManager::getInstance().addModule<BlockESP>(BlockESP::getInstance());
		ModuleManager::getInstance().addModule<ChestESP>(ChestESP::getInstance());
	}
}

struct Process
{
	DWORD pid;
	HWND window;
};

BOOL CALLBACK EnumWindowsCallback(_In_ HWND hwnd, _In_ LPARAM lParam)
{
	Process* p_process = (Process*)lParam;
	DWORD pid = 0;
	GetWindowThreadProcessId(hwnd, &pid);
	if (pid == p_process->pid
		&& GetWindow(hwnd, GW_OWNER) == NULL
		&& IsWindowVisible(hwnd)
		&& GetConsoleWindow() != hwnd
		) {
		p_process->window = hwnd;
		return FALSE;
	}
	return TRUE;
}

HWND getCurrentWindow()
{
	HANDLE current = GetCurrentProcess();
	Process process = { GetProcessId(current) };
	CloseHandle(current);
	EnumWindows(&EnumWindowsCallback, (LPARAM)&process);
	return process.window;
}

std::string getWindowName(HWND hwnd)
{
	char str[64];
	GetWindowTextA(hwnd, str, 64);
	return std::string(str);
}

void Base::checkVersion() {
	auto window = getCurrentWindow();
	auto name = getWindowName(window);
	if (JNIHelper::IsVanilla()) {
		if (name.find("Badlion") != -1) {
			version = BADLION;
			return;
		}
		version = VANILLA_1_8_9;
		return;
	}
	if (JNIHelper::IsForge())
	{
		if (name.find("1.12.2") != -1 || name.find("花雨庭") != -1)
			version = FORGE_1_12_2;
		if (name.find("1.7.10") != -1)
			version = FORGE_1_7_10;
		if (name.find("1.8.9") != -1)
			version = FORGE_1_8_9;
		if (name.find("Lunar") != -1)
		{
			version = LUNAR_1_8_9;
			isObfuscate = false;
		}
		jint count;
		jfieldID* fields;

		Java::Jvmti->GetClassFields(JNIHelper::ForgeFindClass("net.minecraft.client.Minecraft"), &count, &fields);
		for (int i = 0; i < count; i++)
		{
			char* sign;
			char* name;
			Java::Jvmti->GetFieldName(JNIHelper::ForgeFindClass("net.minecraft.client.Minecraft"), fields[i], &name, &sign, 0);
			if (std::string(name).find("thePlayer") != -1) {
				isObfuscate = false;
			}
			else if (std::string(name).find("player") != -1)
			{
				isObfuscate = false;
			}
			isObfuscate = true;
		}
		return;
	}
	if (JNIHelper::ForgeFindClass("net.minecraft.util.math.RayTraceResult$Type") != nullptr)
		version = FORGE_1_12_2;
}

void Base::handleEventKey(int key) {
	ModuleManager::getInstance().ProcessKeyEvent(key);
}

void Base::Kill()
{
	SDK::Minecraft->gameSettings->RestoreFullscreenKey();
	if (Borderless::Enabled)
		Borderless::Restore(Menu::HandleWindow);
	SDK::Clean();
	StrayCache::DeleteRefs();
	auto og = GetProcAddress(GetModuleHandle("lwjgl64.dll"), "Java_org_lwjgl_opengl_WindowsDisplay_nUpdate");
	JNINativeMethod native[] = {
		{const_cast<char*>("nUpdate"), const_cast<char*>("()V"), (void*)(og)} };
	std::cout << "0g: " << std::hex << std::uppercase << og << std::endl;
	if (og != nullptr)
	{
		jclass clazz{};
		Java::AssignClass("org.lwjgl.opengl.WindowsDisplay", clazz);
		if (!clazz)
		{
			std::cout << "Unable to find windowsDisplay Class" << std::endl;
			Java::Env->FindClass("org/lwjgl/opengl/WindowsDisplay");
		}
		if (clazz)
		{
			Java::Env->RegisterNatives(clazz, native, sizeof(native) / sizeof(JNINativeMethod));
		}
		else {
			std::cout << "Unable to find windowsDisplay Class 2" << std::endl;
		}
	}
	Java::Kill();
	Menu::Kill();
	Logger::Kill();
	ModuleManager::getInstance().clean();
	WebServerManager::getInstance().detach();
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}