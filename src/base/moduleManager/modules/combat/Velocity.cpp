#include "velocity.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"
#include "../../../util/math/math.h"
Velocity::Velocity() : AbstractModule("Velocity", Category::COMBAT,"Cancel the knockback towards you.") {
	this->addValue(FloatType, HorizontalValue);
	this->addValue(FloatType, VerticalValue);
	this->addValue(BoolType, OnlyTargetingValue);
	this->addValue(ListType, VelocityModeValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Velocity* Velocity::getInstance() {
	static auto* inst = new Velocity();
	return inst;
}

void Velocity::onDisable() {
}

void Velocity::onEnable() {
}



int counter;
void Velocity::onUpdate(const EventUpdate e)
{
	auto mode = this->VelocityModeValue->getValue();
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;

	Vector3 pos = thePlayer->GetPos();
	Vector2 rot = Vector2(thePlayer->GetRotationYaw(), thePlayer->GetRotationPitch());
	float clamped_yaw = Math::wrapAngleTo180(rot.x);
	float yawToAdd = 0;
	for (CEntityPlayer& p : CommonData::getInstance()->playerEntities.toVector<CEntityPlayer>()) {

		if (!p.isValid() || p.isNULL()) continue;

		if (Java::Env->IsSameObject(p.getInstance(), thePlayer->getInstance())) {
			continue;
		}

		Vector3 targetPos = p.GetPos();

		if (OnlyTargetingValue->getValue() && (targetPos - pos).Dist() >= 5.0f) {
			continue;
		}
		Vector2 target_required_rotation = Math::getAngles(pos, targetPos);

		yawToAdd = target_required_rotation.x - clamped_yaw;

		yawToAdd = Math::wrapAngleTo180(yawToAdd);
		if (!OnlyTargetingValue->getValue() || std::abs(yawToAdd) < 60) {
			if (mode == 0) {
				if (thePlayer->getHurtTime() > 3) {
					Vector3 motion = thePlayer->getMotion();
					motion.x = motion.x * HorizontalValue->getValue();
					motion.y = motion.y * VerticalValue->getValue();
					motion.z = motion.z * HorizontalValue->getValue();


					thePlayer->setMotion(motion);
				}
			}
			else if (mode == 1) {
				if (thePlayer->getHurtTime() > 7 && thePlayer->isOnGround() && counter++ % 2 == 0) {
					POINT pos_cursor;
					GetCursorPos(&pos_cursor);
					thePlayer->jump();
				}
			}
			else if (mode == 2) {
				if (thePlayer->getHurtTime() > 5) {
					thePlayer->setOnGround(true);
				}
			}
			else if (mode == 3) {
				if (thePlayer->getHurtTime() > 5) {
					thePlayer->set_speed(thePlayer->get_speed());
				}
			}
		}
	}
	

}

void Velocity::RenderMenu()
{

	ImGui::BeginChild("velocity", ImVec2(320, 426), true);
	{

		Menu::DoToggleButtonStuff(2134078, "Toggle Velocity", this);
		ImGui::Separator();
		Menu::DoToggleButtonStuff(3456411312, "Only While Targeting", this->OnlyTargetingValue->getValuePtr());

		if (this->VelocityModeValue->getValue() == 0) {
			Menu::DoSliderStuff(248913712347, "Horizontal", this->HorizontalValue->getValuePtr(), 0.f, 1.f);
			Menu::DoSliderStuff(2489137, "Vertical", this->VerticalValue->getValuePtr(), 0.f, 1.f);
		}
		ImGui::Combo("Mode", this->VelocityModeValue->getValuePtr(), this->VelocityModeValue->getDescs(), 4);
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);

	ImGui::BeginChild("velocity2", ImVec2(320, 426), true);
	{

		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();

}
