#include "menu.h"
#include "../util/logger.h"
#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../moduleManager/AbstractModule.h"

void Menu::Init()
{
	Menu::Title = "NoBoay internal | rip lunar";
	Menu::Initialized = false;
	Menu::Open = false;
	Menu::Keybind ='L';

	Menu::PlaceHooks();
}
void Menu::DoCombo(ModeValue* value) {
	ImGui::Combo(value->getName().c_str(), value->getValuePtr(), value->getDescs(), (int)value->getModes().size());
}

void Menu::DoSliderStuff(int id, const char* text, float* bruh, float min, float max) {

	ImGui::SliderFloat(text, bruh, min, max);
	return;

}

void Menu::DoToggleButtonStuff(int id, const char* text, bool* bruh) {
	ImGui::Checkboxx(text, image::check, bruh);
	return;

}



void Menu::DoToggleButtonStuff(int id, const char* text, AbstractModule* module) {
	ImGui::Checkboxx(text, image::check, module);
	return;

}


void Menu::Kill()
{
	Menu::Open = false;
	Menu::RemoveHooks();
	wglMakeCurrent(Menu::HandleDeviceContext, Menu::OriginalGLContext);
	wglDeleteContext(Menu::MenuGLContext);
	ImGui::DestroyContext();
}

void Menu::PlaceHooks()
{
	Menu::Hook_wglSwapBuffers();
	//Menu::LoadAllGameHook();
	//Menu::HookUpdate();
}

void Menu::RemoveHooks()
{
	Menu::Unhook_wndProc();
	Menu::Unhook_wglSwapBuffers();
	//	Menu::RemoveAllGameHook();
		//Menu::UnhookUpdate();
}
