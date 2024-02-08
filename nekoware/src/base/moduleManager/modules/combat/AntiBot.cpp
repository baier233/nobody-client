#include "antibot.h"
#include "../../../menu/menu.h"

Antibot::Antibot() : AbstractModule("Antibot", Category::COMBAT ,"Anti Bot") {
}

Antibot* Antibot::getInstance() {
	static auto* inst = new Antibot();
	return inst;
}

void Antibot::onDisable() {
}

void Antibot::onEnable() {

}

void Antibot::RenderMenu()
{
	ImGui::BeginChild("Antib", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(696969, "Toggle Antibot", this);
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Antib2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}
