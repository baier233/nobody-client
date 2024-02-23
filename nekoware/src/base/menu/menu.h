#pragma once

#include <string>
#include <Windows.h>
#include <vector>

#include "../../../ext/imgui/imgui.h"
#include "../moduleManager/AbstractModule.h"

typedef void(*callback)();
typedef bool(*callback2)();

ImTextureID glLoadTextureFromMemory(const unsigned char* buffer, int size);

struct Menu
{
	inline static const ImColor watermarkColor = ImColor(0, 0, 200);
	static void Init();
	static void GlitchText(const char* text, ImVec2 pos, ImColor col);
	static void Kill();

	static inline std::string Title;
	static inline bool Open;
	static inline int Keybind;
	static inline ImFont* Font;
	static inline bool Initialized;

	static void SetupImgui();
	static void RenderMenu();

	static void DoSliderStuff(int id, const char* text, float* bruh, float min, float max);
	static void DoToggleButtonStuff(int id, const char* text, bool* bruh);
	static void DoToggleButtonStuff(int id, const char* text, AbstractModule* module);

	static inline HWND HandleWindow;
	static inline HDC HandleDeviceContext;

	static inline HGLRC OriginalGLContext;
	static inline HGLRC MenuGLContext;

	static void PlaceHooks();
	static void RemoveHooks();

	static void Hook_wglSwapBuffers();
	static void Hook_wndProc();

	static void Unhook_wglSwapBuffers();
	static void Unhook_wndProc();

};

