#include "../menu.h"

#include <gl/GL.h>
#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <mutex>
#include <Shlobj.h>
#include "../../../../ext/minhook/minhook.h"
#include "../../../../ext/imgui/imgui.h"
#include "../../../../ext/imgui/imgui_impl_win32.h"
#include "../../../../ext/imgui/imgui_impl_opengl3.h"
#include "../../util/logger.h"
#include "../../util/trimmer.h"
#include "../../moduleManager/modules/visual/Xray.h"
#include "../../moduleManager/modules/visual/BlockESP.h"
#include "../../base.h"
#include "../Console/Console.h"
std::once_flag setupFlag;
std::atomic_flag clipCursor = ATOMIC_FLAG_INIT;
RECT originalClip;

typedef bool(__stdcall* template_wglSwapBuffers) (HDC hdc);
template_wglSwapBuffers original_wglSwapBuffers;
bool __stdcall hook_wglSwapBuffers(_In_ HDC hdc)
{
	glPushMatrix();
	Menu::HandleDeviceContext = hdc;
	Menu::HandleWindow = WindowFromDC(hdc);
	Menu::OriginalGLContext = wglGetCurrentContext();

	std::call_once(setupFlag, [&] {
		Menu::Hook_wndProc();
		Menu::SetupImgui();
		});
	glDepthFunc(GL_LEQUAL);

	if (Xray::getInstance()->getToggle())
		glDepthFunc(GL_ALWAYS);

	wglMakeCurrent(Menu::HandleDeviceContext, Menu::MenuGLContext);
	//glDepthFunc(GL_LEQUAL);
	ImGui_ImplOpenGL3_NewFrame();
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
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	glPopMatrix();
	return original_wglSwapBuffers(hdc);
}

void Menu::Hook_wglSwapBuffers()
{
	LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");
	MH_CreateHook(wglSwapBuffers, (LPVOID)hook_wglSwapBuffers, (LPVOID*)&original_wglSwapBuffers);
	MH_EnableHook(wglSwapBuffers);

}

void Menu::Unhook_wglSwapBuffers()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
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
	//Manrope_Semmi_Font = io.Fonts->AddFontFromMemoryTTF(&Main_Font, sizeof Main_Font, 19.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	Benzin_Medium_Font = io.Fonts->AddFontFromMemoryTTF(&Dreamscape_Sans, Dreamscape_Sans_size, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	//Harmony_Regular_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Regular,HarmonyOS_Sans_Regular_size, 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	//Harmony_Bold_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Bold, HarmonyOS_Sans_Bold_size, 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	Manrope_Semmi_Font = io.Fonts->AddFontFromMemoryTTF(&HarmonyOS_Sans_Regular, HarmonyOS_Sans_Regular_size, 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
	Menu::Font = Manrope_Semmi_Font;
	//Benzin_Medium_Font = Harmony_Bold_Font;
	if (image::check == nullptr) image::check = glLoadTextureFromMemory(check_icon, sizeof(check_icon));

	if (image::input == nullptr) image::input = glLoadTextureFromMemory(input_icon, sizeof(input_icon));

	if (image::aimbot == nullptr) image::aimbot = glLoadTextureFromMemory(aimbot_icon, sizeof(aimbot_icon));

	if (image::no_aimbot == nullptr)image::no_aimbot = glLoadTextureFromMemory(no_aimbot_icon, sizeof(no_aimbot_icon));

	if (image::visuals == nullptr) image::visuals = glLoadTextureFromMemory(visuals_icon, sizeof(visuals_icon));

	if (image::drop == nullptr) image::drop = glLoadTextureFromMemory(drop_icon, sizeof(drop_icon));

	if (image::could == nullptr) image::could = glLoadTextureFromMemory(could_icon, sizeof(could_icon));

	if (image::exploits == nullptr) image::exploits = glLoadTextureFromMemory(exploits_icon, sizeof(exploits_icon));

	if (image::keybind == nullptr)  image::keybind = glLoadTextureFromMemory(keybind_icon, sizeof(keybind_icon));

	if (image::arrows == nullptr)  image::arrows = glLoadTextureFromMemory(arrows_icon, sizeof(arrows_icon));

	if (image::iconInfo == nullptr) image::iconInfo = glLoadTextureFromMemory(info, info_size);
	if (image::iconErr == nullptr) image::iconErr = glLoadTextureFromMemory(error, error_size);
	if (image::iconSucc == nullptr) image::iconSucc = glLoadTextureFromMemory(success, success_size);
	if (image::iconWarn == nullptr) image::iconWarn = glLoadTextureFromMemory(waring, waring_size);

	ImGui::GetStyle().ItemSpacing = ImVec2(0, 12);

	ImGui_ImplWin32_Init(Menu::HandleWindow);
	ImGui_ImplOpenGL3_Init();


	Menu::Initialized = true;
}