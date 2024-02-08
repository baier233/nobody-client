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

	ModeValue* mode = new ModeValue("DrawMode", { WireFrame , Fill }, DrawModeList, WireFrame);
	ColorValue* ChamsColor = new ColorValue("ChamsColor", TextColor);
private:
	Chams();
	float TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	enum DrawMode {
		WireFrame,
		Fill
	};
	const char* DrawModeList[2]{ "WireFrame", "Fill" };
};