#include "scaffold.h"
#include "../../../menu/menu.h"
#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;
int count = 0;

Scaffold::Scaffold() : AbstractModule("Scaffold", Category::PLAYER,"Automatically place blocks", 'Y') {
	this->addValue(BoolType, TowerValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Scaffold* Scaffold::getInstance()
{
	static auto* inst = new Scaffold();
	return inst;
}

void Scaffold::onEnable()
{
	if (CommonData::getInstance()->SanityCheck())
	{
		orYaw = SDK::Minecraft->thePlayer->GetRotationYaw();
		orPitch = SDK::Minecraft->thePlayer->GetRotationPitch();
		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw() + 180, SDK::Minecraft->thePlayer->isOnGround() ? 80 : 73));
		count = 0;
	}
}

void Scaffold::onDisable()
{
	if (CommonData::getInstance()->SanityCheck())
		SDK::Minecraft->thePlayer->SetAngles(Vector2(orYaw, orPitch));
	

}

void Scaffold::onUpdate(const EventUpdate e)
{
	
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	jclass blockClass;
	Java::GetInstance()->AssignClass("net.minecraft.item.ItemBlock", blockClass);

	//CMinecraft* mc = SDK::Minecraft;
	count++;
	if (SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1, SDK::Minecraft->thePlayer->GetPos().z)) {
		SDK::Minecraft->thePlayer->setSneak(true);
		//SDK::Minecraft->thePlayer->setMotion(Vector3(0, 100000000000, 0));
	}
	else {
		SDK::Minecraft->thePlayer->setSneak(false);
	}

	if (this->TowerValue->getValue() && !SDK::Minecraft->theWorld->isAirBlock(SDK::Minecraft->thePlayer->GetPos().x, SDK::Minecraft->thePlayer->GetPos().y - 1.5, SDK::Minecraft->thePlayer->GetPos().z) && GetAsyncKeyState(VK_SPACE) & 0x8000) {

		SDK::Minecraft->thePlayer->setMotion(Vector3(0, count % 2 == 0 ? 0.1 : 0.32, 0));
		SDK::Minecraft->thePlayer->setOnGround(true);

		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw(), 90));
	}
	else {
		SDK::Minecraft->thePlayer->SetAngles(Vector2(SDK::Minecraft->thePlayer->GetRotationYaw(), SDK::Minecraft->thePlayer->isOnGround() ? 80 : 75));
	}

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	POINT pos_cursor;
	GetCursorPos(&pos_cursor);
	SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
	SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

	rightLastClickTime = milli;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(8, 14);
	rightNextCps = distrib(gen);

}

void Scaffold::RenderMenu()
{
	ImGui::BeginChild("Scaffold", ImVec2(320, 426), true);
	{

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		ImGui::Checkboxx("Toggle Scaffold", image::check,this);
		ImGui::Checkboxx("Tower",image::check ,this->TowerValue->getValuePtr());

		
	}
	ImGui::EndChild();
}
