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

//#include <curl/curl.h>
#define M_PI 3.1415926

/*
This file is mainly for optimization purposes, instead of loading the data inside each module, we just load them here and then pass the data onto
the modules that will eventually use them.

The modules that write data will still need to access required java objects to do so.
*/

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

	//struct PlayerData{
	//	CEntityPlayer obj;
	//	Vector3 pos;
	//	Vector3 lastPos;
	//	BoundingBox boundingBox;
	//	std::string name;
	//	float height;
	//	float health;
	//	float maxHealth;
	//};

	enum Direction {
		NONE, LEFT, RIGHT, BACKWARDS, FORWARDS
	};

	List playerEntities{};
	//List loadedEntities{};

	void UpdateData(const EventUpdate e)
	{
		if (!SanityCheck()) return;
		*SDK::Minecraft->thePlayer = SDK::Minecraft->getThePlayer();
		*SDK::Minecraft->theWorld = SDK::Minecraft->getTheWorld();
		*SDK::Minecraft->activeRenderInfo = CActiveRenderInfo();
		//*SDK::Minecraft->netHandler = SDK::Minecraft->getNetHandler();
		//*SDK::Minecraft->ingameGUI = SDK::Minecraft->getIngameGUI();
		modelView = SDK::Minecraft->activeRenderInfo->ModelViewMatrix();
		projection = SDK::Minecraft->activeRenderInfo->ProjectionMatrix();
		fov = SDK::Minecraft->gameSettings->GetFOV();
		thirdPersonView = SDK::Minecraft->gameSettings->GetThirdPersonView();
		playerEntities = SDK::Minecraft->theWorld->GetPlayerList();
		//loadedEntities = SDK::Minecraft->theWorld->GetLoadedEntityList();
		float ySubtractValue = 3.4;
		if (SDK::Minecraft->thePlayer->IsSneaking())
			ySubtractValue -= .175f;
		isCombat = false;
		renderPos = SDK::Minecraft->renderManager->RenderPos() + Vector3{ 0, ySubtractValue, 0 };
		renderPartialTicks = SDK::Minecraft->timer->GetRenderPartialTicks();



		// Storing all the required data that will be used within modules here just to have one for loop for gathering data
		// the rest of the for loops inside modules will be for actually doing what they need to do


		//std::vector<PlayerData> newData;
		//List playerList = SDK::Minecraft->theWorld->GetPlayerList();
		//for (CEntityPlayer player : playerList.toVector<CEntityPlayer>()) {
		//	newData.push_back(PlayerData{
		//			player,
		//			player.GetPos(),
		//			player.GetLastTickPos(),
		//			player.GetBB().GetNativeBoundingBox(),
		//			player.GetName(),
		//			player.GetHeight(),
		//			player.GetHealth(),
		//			player.GetMaxHealth()
		//		});
		//}
		//nativePlayerList = newData;

		dataUpdated = true; // This entire function is stopped, and this is flipped once the world and or player object appears to be null
		// Mainly for sanity checks for rendering functions, it prevents crashing whenever the user is not in a game because some data
		// might be needed from within the render functions.
	}

	// Return false if sanity check failed

	bool SanityCheck() {

		if (Java::Env->IsSameObject(SDK::Minecraft->getInstance(),NULL))
		{
			return false;
		}

		if (Java::Env->IsSameObject(SDK::Minecraft->getTheWorld().getInstance(), NULL) ||
			Java::Env->IsSameObject(SDK::Minecraft->getThePlayer().getInstance(), NULL) ||
			Java::Env->IsSameObject(SDK::Minecraft->GetRenderManager().getInstance(), NULL))
		{
			CommonData::dataUpdated = false;
			return false;
		}
		/*if (Java::Env->IsSameObject(SDK::Minecraft->thePlayer->getInstance(), NULL))
		{
			*SDK::Minecraft->thePlayer = SDK::Minecraft->getThePlayer();
		}
		if (Java::Env->IsSameObject(SDK::Minecraft->theWorld->getInstance(), NULL))
		{
			*SDK::Minecraft->theWorld = SDK::Minecraft->getTheWorld();
		}*/
		return true;
	}
};