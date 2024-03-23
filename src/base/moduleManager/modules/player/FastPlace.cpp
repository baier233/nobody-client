#include "fastplace.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"



Fastplace::Fastplace() : AbstractModule("Fastplace", Category::PLAYER,"FastPlace.") {
	this->addValue(FloatType, DelayValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Fastplace* Fastplace::getInstance() {
	static auto* inst = new Fastplace();
	return inst;
}

void Fastplace::onDisable() {
}

void Fastplace::onEnable() {
}

void Fastplace::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	SDK::GetInstance()->Minecraft->setRightClickDelayTimer((int)DelayValue->getValue());
}

void Fastplace::RenderMenu()
{
	ImGui::BeginChild("fastplace", ImVec2(320, 426), true);
	{

		ImGui::Checkboxx("Toggle Fastplace",image::check, this);

		ImGui::SliderFloat("Delay", this->DelayValue->getValuePtr(), 0.f, 6.f);

	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("fastplace2", ImVec2(320, 426), true);
	{

		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);

	}
	ImGui::EndChild();
}
