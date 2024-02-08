#include "Xray.h"
#include "../../../menu/menu.h"



Xray::Xray() : AbstractModule("Xray", Category::VISUAL, "Xray") {
}

Xray* Xray::getInstance() {
	static auto* inst = new Xray();
	return inst;
}

void Xray::onDisable() {
}

void Xray::onEnable() {
}

void Xray::RenderMenu()
{
	ImGui::BeginChild("Xray", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(3465, "Toggle Xray", this);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Xray2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

