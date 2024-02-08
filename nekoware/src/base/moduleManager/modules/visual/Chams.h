#pragma once
#include "../../AbstractModule.h"
#include <list>
#include <gl/GL.h>
#include "../../../../../ext/glm/glm.hpp"
#include "../../../../../ext/glm/gtc/type_ptr.hpp"
#include "../../../menu/menu.h"

class Chams :public AbstractModule {
public:
	static Chams* getInstance();
	void onEnable();
	void onDisable();
	void RenderUpdate();
	void RenderMenu();

private:
	Chams();
};