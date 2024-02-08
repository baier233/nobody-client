#include "eagle.h"
#include "../../commonData.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"


Eagle::Eagle() : AbstractModule("Eagle", Category::PLAYER,"Automatically stealth.") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Eagle* Eagle::getInstance() {
	static auto* inst = new Eagle();
	return inst;
}

void Eagle::onDisable() {
	if (!CommonData::getInstance()->SanityCheck())
		return;
	SDK::Minecraft->thePlayer->setSneak(false);

}

void Eagle::onEnable() {
}


void Eagle::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	
	if (!CommonData::getInstance()->SanityCheck()) return;

	if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
		SDK::Minecraft->thePlayer->setSneak(true);
	}
	else {
		SDK::Minecraft->thePlayer->setSneak(false);
	}
}

void Eagle::RenderMenu()
{
	ImGui::BeginChild("Eagle", ImVec2(320, 426), true);
	{
		ImGui::Checkboxx("Toggle Eagle",image::check, this);
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Eagle2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}
