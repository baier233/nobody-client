#include "../menu.h"

#include <gl/GL.h>
#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <mutex>
#include <Shlobj.h>
#include "../../../../ext/imgui/imgui.h"
#include "../../../../ext/imgui/imgui_impl_win32.h"
#include "../../../../ext/imgui/imgui_impl_opengl3.h"
#include "../../../../ext/imgui/imgui_impl_opengl2.h"
#include "../../util/logger.h"
#include "../../util/trimmer.h"
#include "../../moduleManager/modules/visual/Xray.h"
#include "../../moduleManager/modules/visual/BlockESP.h"
#include "../../base.h"
std::once_flag setupFlag;
std::atomic_flag clipCursor = ATOMIC_FLAG_INIT;
RECT originalClip;

#include "../../util/TitanHook.h"


struct Context
{
	RECT LastWindowRect;
}currentCtx{ .LastWindowRect = RECT{0,0,0,0} };


static void windowResizeHandler(RECT rect,int width, int height) {

	Menu::Kill();
	Menu::Initialized = false;
	bg = nullptr;
	bg_cs = nullptr;
	Logotip = nullptr;
	Menu::PlaceHooks();
}



typedef bool(__stdcall* template_wglSwapBuffers) (HDC hdc);
TitanHook<template_wglSwapBuffers> wglSwapBuffersHook;

bool __stdcall hook_wglSwapBuffers(_In_ HDC hdc)
{


	if (Base::version != FORGE_1_18_1) glPushMatrix();

	Menu::HandleDeviceContext = hdc;
	Menu::HandleWindow = WindowFromDC(hdc);
	Menu::OriginalGLContext = wglGetCurrentContext();

	//TODO : Migrate it to WndProc
	{
		static bool Init = false;
		RECT windowRect;
		GetWindowRect(Menu::HandleWindow, &windowRect);

		int lastWindowWidth = currentCtx.LastWindowRect.right - currentCtx.LastWindowRect.left;
		int lastWindowHeight = currentCtx.LastWindowRect.bottom - currentCtx.LastWindowRect.top;

		int windowWidth = windowRect.right - windowRect.left;
		int windowHeight = windowRect.bottom - windowRect.top;

		bool haveResized = (windowWidth != lastWindowWidth || windowHeight != lastWindowHeight) && lastWindowHeight != 0;
		if (haveResized && Init)
		{
			//std::cout << "Handling Resize" << std::endl;
			windowResizeHandler(windowRect, windowWidth, windowHeight);
		}

		Init = true;
		currentCtx.LastWindowRect = windowRect;
	}
	

	if (!Menu::Initialized)
	{
		Menu::Hook_wndProc();
		Menu::SetupImgui();
	}
	glDepthFunc(GL_LEQUAL);

	if (Xray::getInstance()->getToggle())
		glDepthFunc(GL_ALWAYS);

	wglMakeCurrent(Menu::HandleDeviceContext, Menu::MenuGLContext);
	//glDepthFunc(GL_LEQUAL);
	if (Base::version == LUNAR_1_12_2 || Base::version == LUNAR_1_8_9)
	{
		ImGui_ImplOpenGL3_NewFrame();
	}
	else {
		ImGui_ImplOpenGL2_NewFrame();
	}
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();


	if (Menu::Open)
	{
		//if (clipCursor.test_and_set()) GetClipCursor(&originalClip);

		//ClipCursor(NULL);
		Menu::RenderMenu();
		//Console::getInstance().Render();
	}
	else
	{
		// checking if originalClip is valid
		if (originalClip.right > originalClip.left && originalClip.bottom > originalClip.top)
		{
			ClipCursor(&originalClip);
			clipCursor.clear();
		}
	}

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Overlay", nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoFocusOnAppearing |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoBackground);

	Base::RenderLoop(hdc);

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	if (Base::version == LUNAR_1_12_2 || Base::version == LUNAR_1_8_9)
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	else {
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	if (Base::version != FORGE_1_18_1) glPopMatrix();
	
	return wglSwapBuffersHook.GetOrignalFunc()(hdc);
}

void Menu::Hook_wglSwapBuffers()
{
	LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	wglSwapBuffersHook.InitHook(wglSwapBuffers, hook_wglSwapBuffers);
	wglSwapBuffersHook.SetHook();

}

void Menu::Unhook_wglSwapBuffers()
{
	wglSwapBuffersHook.RemoveHook();
}

#include "../../../../ext/imgui/main.h"
#include "../stb_image.h"
#include "../Image.h"

inline ImTextureID glLoadTextureFromMemory(const unsigned char* buffer, int size) {


	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	stbi_uc* data = stbi_load_from_memory(buffer, size, &width, &height, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, false, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	ImTextureID my_tex_id = (void*)(intptr_t)textureID;
	return my_tex_id;
}

#include "../HarmonyOS_Sans_Regular.h"
#include "../neverlose900.h"
#include "../neverlose500.h"
#include "../Dreamscape_Sans.h"
#include "../../Resource/image/info.h"
#include "../../Resource/image/error.h"
#include "../../Resource/image/success.h"
#include "../../Resource/image/waring.h"


void Menu::SetupImgui()
{
	Menu::MenuGLContext = wglCreateContext(Menu::HandleDeviceContext);
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::MenuGLContext);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLint m_viewport[4];
	glGetIntegerv(GL_VIEWPORT, m_viewport);

	glOrtho(0, m_viewport[2], m_viewport[3], 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();


	ImGuiStyle& style = ImGui::GetStyle();
	if (!Menu::Initialized)
	{
		Benzin_Medium_Font = io.Fonts->AddFontFromMemoryTTF(&Dreamscape_Sans, Dreamscape_Sans_size, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		//Harmony_Regular_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Regular,HarmonyOS_Sans_Regular_size, 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		//Harmony_Bold_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Bold, HarmonyOS_Sans_Bold_size, 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
		Manrope_Semmi_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Regular, HarmonyOS_Sans_Regular_size, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());

		Menu::nlBold14 = io.Fonts->AddFontFromMemoryTTF(&neverlose900, neverlose900_size, 14.f, NULL);
		Menu::nl14 = io.Fonts->AddFontFromMemoryTTF(&neverlose500, neverlose500_size, 14.f, NULL);
		Menu::Font = Manrope_Semmi_Font;
		//Benzin_Medium_Font = Harmony_Bold_Font;
		image::check = glLoadTextureFromMemory(check_icon, sizeof(check_icon));

		image::input = glLoadTextureFromMemory(input_icon, sizeof(input_icon));

		image::aimbot = glLoadTextureFromMemory(aimbot_icon, sizeof(aimbot_icon));

		image::no_aimbot = glLoadTextureFromMemory(no_aimbot_icon, sizeof(no_aimbot_icon));

		image::visuals = glLoadTextureFromMemory(visuals_icon, sizeof(visuals_icon));

		image::drop = glLoadTextureFromMemory(drop_icon, sizeof(drop_icon));

		image::could = glLoadTextureFromMemory(could_icon, sizeof(could_icon));

		image::exploits = glLoadTextureFromMemory(exploits_icon, sizeof(exploits_icon));

		image::keybind = glLoadTextureFromMemory(keybind_icon, sizeof(keybind_icon));

		image::arrows = glLoadTextureFromMemory(arrows_icon, sizeof(arrows_icon));

		image::iconInfo = glLoadTextureFromMemory(info, info_size);
		image::iconErr = glLoadTextureFromMemory(error, error_size);
		image::iconSucc = glLoadTextureFromMemory(success, success_size);
		image::iconWarn = glLoadTextureFromMemory(waring, waring_size);

		
		

		ImGui::GetStyle().ItemSpacing = ImVec2(0, 12);
	}
	

	ImGui_ImplWin32_Init(Menu::HandleWindow);
	if (Base::version == LUNAR_1_12_2 || Base::version == LUNAR_1_8_9)
	{
		ImGui_ImplOpenGL3_Init();
	}
	else {
		ImGui_ImplOpenGL2_Init();
	}

	

	Menu::Initialized = true;
}