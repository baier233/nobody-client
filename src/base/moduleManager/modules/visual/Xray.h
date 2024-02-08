#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>
#include "../../commonData.h"
class Xray : public AbstractModule
{
public:
	static Xray* getInstance();
	void onEnable();
	void onDisable();
	void RenderMenu();
private:
	Xray();
};