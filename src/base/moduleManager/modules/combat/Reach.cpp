#include "reach.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include "../../../util/logger.h"
#include "../../../java/java.h"
#include "../../../util/math/math.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

#include <chrono>

//
//
// NOTICE:
//
// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
//
// https://github.com/zorftw/gasper-cpp
//
//

Reach::Reach() : AbstractModule("Reach", Category::COMBAT,"Allows you to hit players farther away.") {
	this->addValue(FloatType, ReachDistanceValue);
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

Reach* Reach::getInstance() {
	static auto* inst = new Reach();
	return inst;
}

void Reach::onDisable() {
}

void Reach::onEnable() {
}


std::chrono::steady_clock::time_point lastUpdate;
void Reach::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;

	std::chrono::steady_clock::time_point nanoTime = std::chrono::high_resolution_clock::now();

	// Calculate the elapsed time in nanoseconds
	float elapsed = (float) std::chrono::duration_cast<std::chrono::nanoseconds>(nanoTime - lastUpdate).count() / 1000000;
	if (elapsed < 20)
		return;
	else
		lastUpdate = nanoTime;

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
	List playerList = CommonData::getInstance()->playerEntities;

	Vector2 playerAngles = thePlayer->GetAngles();
	Vector3 playerPos = thePlayer->GetPos();

	//
	//
	// NOTICE:
	//
	// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
	//
	// https://github.com/zorftw/gasper-cpp
	//
	//


	for (CEntityPlayer target : playerList.toVector<CEntityPlayer>())
	{
		if (!target.isValid() || target.isNULL()) continue;

		float distance = ReachDistanceValue->getValue();
		if (Java::Env->IsSameObject(thePlayer->getInstance(), target.getInstance())) continue;

		BoundingBox targetBB = target.GetBB().GetNativeBoundingBox();

		float hypothenuseDistance = (float) sqrt(pow((playerPos - target.GetPos()).x, 2) + pow((playerPos - target.GetPos()).z, 2));

		if (distance > hypothenuseDistance)
			distance -= hypothenuseDistance;

		float difference = Math::wrapAngleTo180(playerAngles.x - Math::getAngles(playerPos, target.GetPos()).x);

		if (std::abs(difference) > 180.0f)
			continue;

		float cos = std::cos(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).x + 90.0f));
		float sin = std::sin(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).x + 90.0f));
		float cosPitch = std::cos(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).y));
		float sinPitch = std::sin(Math::degToRadiants(Math::getAngles(playerPos, target.GetPos()).y));

		float x = target.GetPos().x - (cos * distance * cosPitch);
		float y = target.GetPos().y + (distance * sinPitch);
		float z = target.GetPos().z - (sin * distance * cosPitch);

		float entityWidth = 0.6f;
		float bbWidth = entityWidth / 2.0f;

		BoundingBox newBB{
			(double) x - bbWidth,
			(double) y,
			//targetBB.minY,
			(double) z - bbWidth,

			(double) x + bbWidth,
			(double) y + 2,
			//targetBB.maxY,
			(double) z + bbWidth
		};

		target.SetBB(newBB);
	}

}

//
//
// NOTICE:
//
// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
//
// https://github.com/zorftw/gasper-cpp
//
//


void Reach::RenderMenu()
{


	ImGui::BeginChild("reach", ImVec2(320, 426), true);
	{

		Menu::DoToggleButtonStuff(230044, "Toggle Reach", this);
		ImGui::Separator();

		Menu::DoSliderStuff(560117, "Reach Distance", this->ReachDistanceValue->getValuePtr(), 0, 4);

	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);
	
	ImGui::BeginChild("reach2", ImVec2(320, 426), true);
	{

		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);

	}
	ImGui::EndChild();

}
