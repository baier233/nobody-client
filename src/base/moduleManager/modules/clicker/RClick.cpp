#include "RClick.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"
#include "../../../eventManager/EventManager.hpp"
#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;

RClick::RClick() : AbstractModule("RClick", Category::CLICKER,"Automatically click your right button") {
	this->addValue(FloatType, rightMinCpsValue);
	this->addValue(FloatType, rightMaxCpsValue);
	this->addValue(BoolType, blocksOnlyValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

RClick* RClick::getInstance() {
	static auto* inst = new RClick();
	return inst;
}

void RClick::onDisable() {
}

void RClick::onEnable() {
}



void RClick::onUpdate(const EventUpdate e)
{
	if (!getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	jclass blockClass{};
	if (Base::version == FORGE_1_18_1)
	{
		blockClass = StrayCache::GetInstance()->itemBlock_class;
	}
	else {
		Java::GetInstance()->AssignClass("net.minecraft.item.ItemBlock", blockClass);
	}
	if (SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().getInstance() == NULL) return;
	if (this->blocksOnlyValue->getValue() && !Java::GetInstance()->Env->IsInstanceOf(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetItem().getInstance(), blockClass)) return;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	if (GetAsyncKeyState(VK_RBUTTON) && 1) {
		POINT pos_cursor;

		GetCursorPos(&pos_cursor);
		PostMessageA(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		PostMessageA(Menu::HandleWindow, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		rightLastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(this->rightMinCpsValue->getValue(), this->rightMaxCpsValue->getValue());
		rightNextCps = distrib(gen);
	}
}

void RClick::RenderMenu()
{
	
	ImGui::BeginChild("RClick", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(2344, "Toggle Right Auto Clicker", this);
		Menu::DoSliderStuff(3280, "Min CPS", this->rightMinCpsValue->getValuePtr(), 1, 20);
		Menu::DoSliderStuff(675, "Max CPS", this->rightMaxCpsValue->getValuePtr(), 1, 20);
		if (this->rightMinCpsValue->getValue() > this->rightMaxCpsValue->getValue()) {
			*this->rightMinCpsValue->getValuePtr() = rightMaxCpsValue->getValue();
		}
		Menu::DoToggleButtonStuff(73451, "Blocks Only", this->blocksOnlyValue->getValuePtr());

	}
	ImGui::EndChild();
}