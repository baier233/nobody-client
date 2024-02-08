#pragma once
#include "../../AbstractModule.h"
#include <list>
#include <gl/GL.h>
#include "../../../../../ext/glm/glm.hpp"
#include "../../../../../ext/glm/gtc/type_ptr.hpp"
#include "../../../menu/menu.h"

#include "../../Value.h"
class ChestESP :public AbstractModule {
public:
	static ChestESP* getInstance();
	void onEnable();
	void onDisable();
	void RenderUpdate();
	void RenderMenu();


	BoolValue* bypassObsValue = new BoolValue("OBS Bypass", false);
private:
	ChestESP();

};