#include "fullbright.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

Fulbright::Fulbright() : AbstractModule("Fulbright", Category::VISUAL,"FullBright.") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Fulbright* Fulbright::getInstance() {
	static auto* inst = new Fulbright();
	return inst;
}

void Fulbright::onDisable() {
	SDK::GetInstance()->Minecraft->gameSettings->SetGamma(this->currentGamma);
}

void Fulbright::onEnable() {
	this->currentGamma = SDK::GetInstance()->Minecraft->gameSettings->GetGamma();
}

void Fulbright::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	SDK::GetInstance()->Minecraft->gameSettings->SetGamma(100.f);
}

void Fulbright::RenderMenu()
{
	ImGui::BeginChild("Fullbright", ImVec2(320, 426), true);
	{
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(568, "Toggle Fullbright", this);
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);
	
	ImGui::BeginChild("Fullbright2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

