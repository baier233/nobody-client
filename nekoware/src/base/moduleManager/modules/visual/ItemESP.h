#pragma once
#include "../../AbstractModule.h"
#include "../../commonData.h"
#include "../../../eventManager/EventManager.hpp"
#include "../../../eventManager/events/EventUpdate.hpp"
#include "../../../sdk/net/minecraft/entity/item/EntityItem.h"
#include <gl/GL.h>

class ItemESP : public AbstractModule {
public:
	static ItemESP* getInstance();
	void onEnable();
	void onDisable();
	void RenderUpdate();
	void RenderMenu();
	void onUpdate(EventUpdate e);
private:
	ItemESP();
	std::vector<Vector3D> data;
	std::vector<float> structToVector(const Matrix& matrix);
	void GLRenderBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
};