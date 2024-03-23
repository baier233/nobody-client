#pragma once

#include "../util/math/geometry.h"
#include "../sdk/sdk.h"
#include "../util/logger.h"
#include "../../../ext/jni/jni.h"
#include "AbstractModule.h"
#include "../eventManager/EventManager.hpp"
#include "../eventManager/events/EventUpdate.hpp"
#include "../sdk/java/util/Set.h"
#include "Value.h"

constexpr auto M_PI = 3.1415926;

class CommonData
{
public:
	CommonData() {
		EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { UpdateData(std::forward<decltype(PH1)>(PH1)); });
	}

	static CommonData* getInstance() {
		static auto* inst = new CommonData();
		return inst;
	}
	bool dataUpdated = false;
	bool post = false;
	Matrix modelView;
	Matrix projection;
	Vector3 renderPos;
	float renderPartialTicks;
	float fov;
	int thirdPersonView;

	bool isCombat = false;


	enum Direction {
		NONE, LEFT, RIGHT, BACKWARDS, FORWARDS
	};

	List playerEntities{};
	List loadedTitleEntities{};

	void UpdateData(const EventUpdate e)
	{
		if (!SanityCheck()) return;
		*SDK::GetInstance()->Minecraft->thePlayer = SDK::GetInstance()->Minecraft->getThePlayer();
		*SDK::GetInstance()->Minecraft->theWorld = SDK::GetInstance()->Minecraft->getTheWorld();
		*SDK::GetInstance()->Minecraft->activeRenderInfo = CActiveRenderInfo();
		fov = SDK::GetInstance()->Minecraft->gameSettings->GetFOV();
		thirdPersonView = SDK::GetInstance()->Minecraft->gameSettings->GetThirdPersonView();
		playerEntities = SDK::GetInstance()->Minecraft->theWorld->GetPlayerList();
		modelView = SDK::GetInstance()->Minecraft->activeRenderInfo->ModelViewMatrix();
		projection = SDK::GetInstance()->Minecraft->activeRenderInfo->ProjectionMatrix();
		if (Base::version != FORGE_1_18_1)
		{
			loadedTitleEntities = SDK::GetInstance()->Minecraft->theWorld->GetLoadedTileEntityList();
		}
		float ySubtractValue = 3.4;
		if (SDK::GetInstance()->Minecraft->thePlayer->IsSneaking())
			ySubtractValue -= .175f;
		isCombat = false;

		renderPartialTicks = SDK::GetInstance()->Minecraft->timer->GetRenderPartialTicks();
		if (Base::version == FORGE_1_18_1)
		{
			auto eyeHeight = SDK::GetInstance()->Minecraft->thePlayer->GetEyeHeight();
			auto pos = SDK::GetInstance()->Minecraft->thePlayer->GetPos();
			auto lastTickPos = SDK::GetInstance()->Minecraft->thePlayer->GetLastTickPos();
			double x = (double)lastTickPos.x + ((double)pos.x - (double)lastTickPos.x) * (double)renderPartialTicks;
			double y = (double)lastTickPos.y + ((double)pos.y - (double)lastTickPos.y) * (double)renderPartialTicks;
			double z = (double)lastTickPos.z + ((double)pos.z - (double)lastTickPos.z) * (double)renderPartialTicks;
			renderPos = Vector3{ (float)x,(float)y,(float)z } + Vector3{ 0, ySubtractValue - eyeHeight, 0 };
		}
		else {

			renderPos = SDK::GetInstance()->Minecraft->renderManager->RenderPos() + Vector3{ 0, ySubtractValue, 0 };
		}

		dataUpdated = true;
	}

	// Return false if sanity check failed



	bool SanityCheck() {

		if (!Java::GetInstance()->Initialized) {
			Java::GetInstance()->Init();
		}
	
		if (!StrayCache::GetInstance()->initialized) {
			StrayCache::GetInstance()->Initialize();
		}

		if (!SDK::GetInstance()->Minecraft) {
			SDK::GetInstance()->Init();
		}

		if (Java::GetInstance()->Env->IsSameObject(SDK::GetInstance()->Minecraft->getInstance(), NULL))
		{
			return false;
		}

		if (Java::GetInstance()->Env->IsSameObject(SDK::GetInstance()->Minecraft->getTheWorld().getInstance(), NULL) ||
			Java::GetInstance()->Env->IsSameObject(SDK::GetInstance()->Minecraft->getThePlayer().getInstance(), NULL))
		{
			CommonData::dataUpdated = false;
			return false;
		}
		if (Base::version != FORGE_1_18_1 && Java::GetInstance()->Env->IsSameObject(SDK::GetInstance()->Minecraft->GetRenderManager().getInstance(), NULL))
		{

			CommonData::dataUpdated = false;
			return false;

		}
		return true;
	}
};