#pragma once
#include "../../AbstractModule.h"
#include "../../commonData.h"
#include "../../../eventManager/EventManager.hpp"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../../sdk/net/minecraft/tileentity/TileEntity.h"
#include "../../../sdk/net/minecraft/tileentity/TileEntityBed.h"

#include "../../../menu/menu.h"

class BedESP :public AbstractModule {
public:
	static BedESP* getInstance();
	void onEnable();
	void onDisable();
	void RenderUpdate();
	void RenderMenu();
	void onUpdate(EventUpdate e);
private:
	BedESP();
	std::vector<Vector3> data;
	void drawSelectionBoundingBox(BoundingBox boundingBox);
	void drawColorBox(BoundingBox boundingBox);
	std::vector<float> structToVector(const Matrix& matrix);
};