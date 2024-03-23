#pragma once
#include "killaura.h"
#include <mutex>
#include <random>
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../util/math/math.h"
#include "../combat/antibot.h"
#include "../combat/teams.h"
long lastClickTime = 0;
int nextCps = 10;
double distance(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return distance(y1 - y2, distance(x1 - x2, z1 - z2));
}

bool isMove() {
	if (!CommonData::getInstance()->SanityCheck()) return NULL;

	CEntityPlayerSP* p = SDK::GetInstance()->Minecraft->thePlayer;

	return (p->getMoveForward() != 0 || p->getMoveStrafe() != 0);
}

Killaura::Killaura() : AbstractModule("Killaura", Category::COMBAT, "Automatically attack players around you.", 'R') {
	this->addValue(FloatType, rangeValue);
	this->addValue(FloatType, leftMinCpsValue);
	this->addValue(FloatType, leftMaxCpsValue);
	this->addValue(FloatType, fovValue);
	this->addValue(BoolType, keepSprintValue);
	this->addValue(BoolType, autoblockValue);
	this->addValue(ListType, killauraMode);
	this->addValue(ListType, targetPriorityListMode);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Killaura* Killaura::getInstance() {
	static auto* inst = new Killaura();
	return inst;
}

void Killaura::onDisable() {
}

void Killaura::onEnable() {
}
bool flag = false;
void Killaura::onUpdate(const EventUpdate e) {
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (SDK::GetInstance()->Minecraft->IsInGuiState()) return;

	List playerList = CommonData::getInstance()->playerEntities;
	CEntityPlayerSP thePlayer = *SDK::GetInstance()->Minecraft->thePlayer;

	Vector3 headPos = thePlayer.GetEyePos();
	Vector2 currentLookAngles = thePlayer.GetAngles();

	CEntityPlayer target;
	float finalDist = FLT_MAX;
	float finalDiff = 370;
	float finalHealth = FLT_MAX;

	float realAimDistance = rangeValue->getValue();

	auto list = playerList.toVector<CEntityPlayer>();
	for (CEntityPlayer player : list)
	{

		if (!player.isValid() || player.isNULL()) continue;
		if (Antibot::getInstance()->getToggle() && Antibot::getInstance()->isBot(player)) {
			continue;
		}

		if (Teams::getInstance()->getToggle() && Teams::getInstance()->isTeam(player)  ) {
			continue;
		}

		if (player.GetName().length() < 0) return;
		if (!Java::GetInstance()->Env->IsSameObject(thePlayer.getInstance(), player.getInstance())) {
			if (!thePlayer.CanEntityBeSeen(player.getInstance())) continue;

			
			float playerHeight{};
			if (Base::version == FORGE_1_18_1)
			{
				playerHeight = target.GetEyeHeight();
			}
			else {
				playerHeight = target.GetHeight() - 0.1;
			}

			Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos() + Vector3(0, playerHeight, 0)).Invert());
			if (difference.x < 0) difference.x = -difference.x;
			if (difference.y < 0) difference.y = -difference.y;
			Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - Math::getAngles(headPos, player.GetPos()).Invert());
			if (differenceFoot.x < 0) differenceFoot.x = -differenceFoot.x;
			if (differenceFoot.y < 0) differenceFoot.y = -differenceFoot.y;

			float angleYaw = currentLookAngles.x - difference.x;

			Vector3 diff = thePlayer.GetPos() - player.GetPos();
			float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));

			if ((abs(difference.x) <= fovValue->getValue()) && dist <= realAimDistance)
			{
				float health = player.GetHealth();
				switch (targetPriorityListMode->getValue())
				{
				case 1:
					if (finalHealth > health)
					{
						target = player;
						finalHealth = health;
					}
					break;

				case 2:
					if (finalDiff > difference.x)
					{
						target = player;
						finalDiff = difference.x;
					}
					break;
				default:
					if (finalDist > dist)
					{
						target = player;
						finalDist = (float)dist;
					}
				}
			}
		}
	}

	if (!target.getInstance()) {
		Vector3 null;
		data = null;
		return;
	}

	if (this->killauraMode->getValue() == Legit) {
		
		Vector3 ePos = target.GetPos();
		Vector3 eLastPos = target.GetLastTickPos();

		float eHeight = target.GetHeight() - 0.1;
		Vector3 eHeadPos = ePos + Vector3(0, eHeight, 0);
		Vector3 eLastHeadPos = eLastPos + Vector3(0, eHeight, 0);


		Vector2 anglesFoot = Math::getAngles(headPos, ePos);
		Vector2 anglesHead = Math::getAngles(headPos, eHeadPos);

		Vector2 difference = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesHead.Invert());
		Vector2 differenceFoot = Math::vec_wrapAngleTo180(currentLookAngles.Invert() - anglesFoot.Invert());

		float offset = 0;

		float targetYaw = currentLookAngles.x + ((difference.x + offset) / 1.0f);

		Vector3 renderPos = CommonData::getInstance()->renderPos;
		float renderPartialTicks = CommonData::getInstance()->renderPartialTicks;

		if (currentLookAngles.y > anglesFoot.y || currentLookAngles.y < anglesHead.y) {
			float targetPitchFoot = currentLookAngles.y + (differenceFoot.y / 1.0f);
			float targetPitchHead = currentLookAngles.y + (difference.y / 1.0f);

			float diffFoot = currentLookAngles.y - targetPitchFoot;
			float diffHead = currentLookAngles.y - targetPitchHead;
			diffFoot = diffFoot < 0 ? -diffFoot : diffFoot;
			diffHead = diffHead < 0 ? -diffHead : diffHead;

			float targetPitch;
			if (diffFoot > diffHead)
			{
				targetPitch = targetPitchHead;
				data = renderPos - Vector3(0, 0.21, 0) - eLastHeadPos + (eLastHeadPos - eHeadPos) * renderPartialTicks;
			}
			else
			{
				targetPitch = targetPitchFoot;
				data = renderPos - Vector3(0, 0.23, 0) - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			}
			thePlayer.SetAngles(Vector2(targetYaw, targetPitch));
		}
		else {
			data = renderPos - eLastPos + (eLastPos - ePos) * renderPartialTicks;
			thePlayer.SetAngles(Vector2(targetYaw, currentLookAngles.y + 0));
		}
	}
	if (!target.getInstance()) {
		return;
	}

	if (keepSprintValue->getValue() && thePlayer.getMoveForward() != 0) {
		thePlayer.setSprint(true);
	}

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;
	if (this->killauraMode->getValue() == Legit) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		CommonData::getInstance()->isCombat = true;
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
	}
	else if (this->killauraMode->getValue() == Normal) {
		//thePlayer.swingItem();
		//CommonData::getInstance()->isCombat = true;
		thePlayer.attackEntity(&thePlayer, target.getInstance());
	}
	if (autoblockValue->getValue() == true && this->killauraMode->getValue() == Legit) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		std::cout << target.GetHealth() << std::endl;
		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		if (isMove())
			thePlayer.set_speed(0.155);
	}
	else if (autoblockValue->getValue() == true && this->killauraMode->getValue() == Normal) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);

		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));

	}


	lastClickTime = milli;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(*this->leftMinCpsValue->getValuePtr(), *this->leftMaxCpsValue->getValuePtr());
	nextCps = distrib(gen);
}
void Killaura::RenderMenu()
{
	
	
	ImGui::BeginChild(this->getName().c_str(), ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(45646, std::string("Toggle " + this->getName()).c_str(), this);
		ImGui::Separator();
		Menu::DoSliderStuff(13141, "Min CPS", this->leftMinCpsValue->getValuePtr(), leftMinCpsValue->getMin(), leftMinCpsValue->getMax());
		Menu::DoSliderStuff(242, "Max CPS", this->leftMaxCpsValue->getValuePtr(), leftMaxCpsValue->getMin(), leftMaxCpsValue->getMax());
		Menu::DoSliderStuff(1324124,this->fovValue->getName().c_str(), this->fovValue->getValuePtr(), this->fovValue->getMin(), this->fovValue->getMax());
		if (leftMinCpsValue->getValue() > leftMaxCpsValue->getValue()) {
			*(leftMaxCpsValue->getValuePtr()) = *(leftMinCpsValue->getValuePtr());
		}
		Menu::DoToggleButtonStuff(2524, "Autoblock", this->autoblockValue->getValuePtr());
		Menu::DoToggleButtonStuff(679067, "Keepsprint", this->keepSprintValue->getValuePtr());
		Menu::DoSliderStuff(34508, this->rangeValue->getName().c_str(), this->rangeValue->getValuePtr(), 3, 6);
		
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild((this->getName()+ "2").c_str(), ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
		ImGui::Combo(this->targetPriorityListMode->getName().c_str(), this->targetPriorityListMode->getValuePtr(), this->targetPriorityListMode->getDescs(), this->targetPriorityListMode->getModes().size());
		ImGui::Combo("Mode", killauraMode->getValuePtr(), killauraMode->getDescs(), 2);
		
	}

	ImGui::EndChild();
}


