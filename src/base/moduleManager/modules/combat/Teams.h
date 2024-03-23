#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>
#include "../../commonData.h"
#include "../../../sdk/net/minecraft/item/ItemArmor.h"

class Teams :public AbstractModule {
public:
	static Teams* getInstance();
	void RenderMenu();
	void onEnable();
	void onDisable();
	bool isTeam(CEntityPlayer p) {


		if (Java::GetInstance()->Env->IsSameObject(p.getInstance(), NULL)) {
			return true;
		}

		if (!p.isValid() || p.isNULL())
		{
			return true;
		}

		CEntityPlayerSP* thePlayer = SDK::GetInstance()->Minecraft->thePlayer;

		if (!thePlayer->GetInventory().isValid()|| p.GetInventory().isNULL())
		{
			return true;
		}

		CItemStack myHead = thePlayer->GetInventory().GetArmorItem(3);
		CItemStack entityHead = p.GetInventory().GetArmorItem(3);

		if (!myHead.isValid() || myHead.isNULL())
		{
			return true;
		}
		
		if (!entityHead.isValid() || entityHead.isNULL())
		{
			return true;
		}

		

		auto colorMe = CItemArmor(myHead.GetItem()).getColor(myHead);
		auto colorU = CItemArmor(entityHead.GetItem()).getColor(entityHead);

		return colorMe ==  colorU;
	}
private:
	Teams();
};