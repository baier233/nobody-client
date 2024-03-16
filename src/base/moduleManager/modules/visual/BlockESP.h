#pragma once
#include "../../../util/math/geometry.h"
#include <vector>
#include <string>
#include "../../commonData.h"
#include <gl/GL.h>
class BlockESP : public AbstractModule
{
public:
	static BlockESP* getInstance();
	void onEnable();
	void onDisable();
	void render(HDC hdc);
	void RenderMenu();
	void onUpdate(EventUpdate e);
private:
	BlockESP();
	NumberValue* m_Radius = new NumberValue("Radius", 25, 0, 90);
	int blockList[255]{ 56, 14, 21, 129, 54, 130, 146, };
	std::vector<std::pair<int, Vector3D>> blockLists;
	uint64_t timer;
	std::vector<float> structToVector(const Matrix& matrix);
	void getBlockColor(double& red, double& green, double& blue, int blockID);
	void GLRenderBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
};