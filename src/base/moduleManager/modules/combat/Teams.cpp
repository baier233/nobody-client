#include "Teams.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"


Teams::Teams() : AbstractModule("Teams", Category::COMBAT,"Teams.") {
}

Teams* Teams::getInstance() {
	static auto* inst = new Teams();
	return inst;
}

void Teams::onDisable() {
}

void Teams::onEnable() {
}

void Teams::RenderMenu()
{
	
	
	ImGui::BeginChild("Teams", ImVec2(320, 426), true);
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(233233, "Toggle Teams", this);


	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Teams2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();


}
