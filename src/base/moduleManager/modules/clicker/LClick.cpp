#include "LClick.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"
#include "../../commonData.h"
#include <chrono>
#include <random>
#include "../../../eventManager/EventManager.hpp"
#include "../../../util/logger.h"
long lastClickTime = 0;
int nextCps = 10;
int count = 0;
LClick::LClick() : AbstractModule("LClick", Category::CLICKER,"Automatically click your left button") {
	this->addValue(FloatType, leftMinCpsValue);
	this->addValue(FloatType, leftMaxCpsValue);
	this->addValue(FloatType, blockHitChanceValue);
	this->addValue(BoolType, ignoreBlocksValue);
	this->addValue(BoolType, blockHitValue);
	this->addValue(BoolType, inInventoryValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}
LClick* LClick::getInstance() {
	static auto* inst = new LClick();
	return inst;
}

void LClick::onDisable() {
}

void LClick::onEnable() {
}



void LClick::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (SDK::GetInstance()->Minecraft->IsInGuiState() && !inInventoryValue->getValue()) return;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;

	if (GetAsyncKeyState(VK_LBUTTON) && 1) {


		auto mouseOver = SDK::GetInstance()->Minecraft->GetMouseOver();
		if (ignoreBlocksValue->getValue() && mouseOver.IsTypeOfBlock()) {
			POINT pos_cursor;
			GetCursorPos(&pos_cursor);
			PostMessageA(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			return;
		}

		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		//CommonData::getInstance()->isCombat = true;
		PostMessageA(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		PostMessageA(Menu::HandleWindow, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		
		if (blockHitValue->getValue() == true && count == blockHitChanceValue->getValue()) {
			PostMessageA(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			PostMessageA(Menu::HandleWindow, WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			count = 0;
		}

		else if (blockHitValue->getValue() == true) {
			
			count++;
		}

		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib((*leftMinCpsValue->getValuePtr()), (*leftMaxCpsValue->getValuePtr()));
		nextCps = distrib(gen);

	}
}

void LClick::RenderMenu()
{
	
	ImGui::BeginChild("autoclicker", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(857834, "Toggle Left Auto Clicker",this);
		Menu::DoSliderStuff(3280, "Min CPS", this->leftMinCpsValue->getValuePtr(), 1, 20);
		Menu::DoSliderStuff(675, "Max CPS", this->leftMaxCpsValue->getValuePtr(), 1, 20);
		Menu::DoToggleButtonStuff(2136, "Ignore Blocks", this->ignoreBlocksValue->getValuePtr());
		Menu::DoToggleButtonStuff(13423, "Blockhit", this->blockHitValue->getValuePtr());
		Menu::DoToggleButtonStuff(135315, "In Inventory", this->inInventoryValue->getValuePtr());
		Menu::DoSliderStuff(342, "Blockhit Chance", this->blockHitChanceValue->getValuePtr(), 1, 50);
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);

	ImGui::BeginChild("autoclicker", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}