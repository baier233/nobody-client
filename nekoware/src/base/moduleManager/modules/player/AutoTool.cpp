#include "autotool.h"
#include "../../commonData.h"
#include "../../../menu/menu.h"
#include "../../../sdk/net/minecraft/item/ItemStack.h"
#include "../../../sdk/net/minecraft/block/Block.h"
#include "../../../sdk/net/minecraft/block/state/IBlockState.h"
#include "../../../sdk/net/minecraft/util/MovingObjectPosition.h"
#include "../../../sdk/net/minecraft/entity/player/InventoryPlayer.h"
#include "../../../sdk/net/minecraft/item/ItemTool.h"
#include <iostream>

AutoTool::AutoTool() : AbstractModule("AutoTool", Category::PLAYER,"Choose the best tool for you.") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

AutoTool* AutoTool::getInstance() {
	static auto* inst = new AutoTool();
	return inst;
}

void AutoTool::onDisable() {
}

void AutoTool::onEnable() {
}

void AutoTool::onUpdate(const EventUpdate e)
{
	if (!this->getToggle()) return;
	if (Menu::Open) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	if (CommonData::getInstance()->isCombat) return;
	if (IsKeyBeingDown(VK_LBUTTON)) {
		float bestSpeed = 1.f;
		int bestSlot = -1;
		CMovingObjectPosition mouseover = SDK::Minecraft->GetMouseOver();
		
		if (!mouseover.isValid() || mouseover.isNULL())
		{
			return;
		}
		CIBlockState blockstate{};
		CBlock block{};
		if (Base::version == FORGE_1_7_10)
		{
			block = mouseover.GetBlock();
			if (!block.isValid()) return;
		}
		else {
			BlockPos blockpos = mouseover.getBlockPos();

			if (!blockpos.isValid())
			{
				return;
			}

			if (SDK::Minecraft->theWorld->isAirBlock(blockpos))
			{
				return;
			}

			blockstate = SDK::Minecraft->theWorld->getBlockState(blockpos);

			if (!blockstate.isValid()) return;
		}
		


		if (Base::version != FORGE_1_12_2 && Base::version != LUNAR_1_12_2 && Base::version != FORGE_1_7_10)
		{
			block = blockstate.getBlock();

			if (!block.isValid()) return;
			
		}
		

	
		auto inventory = SDK::Minecraft->thePlayer->GetInventory();

		for (int i = 0; i <= 8; i++)
		{
			if (!inventory.isValid() || inventory.isNULL()) continue;
			auto item = inventory.GetStackInSlot(i);
			if (!item || item.isNULL()) continue;
			
			float speed;
			if (Base::version == FORGE_1_12_2 || Base::version == LUNAR_1_12_2)
			{
				speed = item.GetStrVsBlock(blockstate);
			} else {
				if (block.isNULL()) continue;
				speed = item.GetStrVsBlock(block);
			}
			if (speed > bestSpeed) {
				bestSpeed = speed;
				bestSlot = i;
			}
		}

		if (bestSlot == -1)
		{
			return;
		}

		inventory.SetCurrentItem(bestSlot);
	}
	
}

bool enabled = false;
void AutoTool::RenderMenu()
{

	ImGui::BeginChild("AutoTool", ImVec2(320, 426), true);
	{
		if (ImGui::Checkboxx("Toggle AutoTool", image::check, &enabled)) {
			this->setToggle(enabled);
		}
	}
	ImGui::EndChild();
	
	ImGui::SameLine(0, 20);

	ImGui::BeginChild("AutoTool2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}
