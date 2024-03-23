#include "ItemESP.h"
#include "../../../menu/menu.h"
ItemESP* ItemESP::getInstance()
{
	static ItemESP* inst = new ItemESP;
	return inst;
}

void ItemESP::onEnable()
{

}

void ItemESP::onDisable()
{
}

void ItemESP::RenderUpdate()
{
	if (!this->getToggle())
		return;
	if (this->data.empty())return;

	auto drawOutlinedBox = [](BoundingBox boundingBox)
		{
			glBegin(3);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glEnd();

			glBegin(3);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glEnd();

			glBegin(1);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
			glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
			glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
			glEnd();
		};

	if (Base::version != FORGE_1_18_1) glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->projection).data());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->modelView).data());
	//drawOutlinedBox(BoundingBox{ d.x - .2, d.y - 0.05, d.z - .2, d.x + .2, d.y - 0.45, d.z + .2 });

	if (Base::version != FORGE_1_18_1) glPushMatrix();
	glEnable(GL_BLEND);
	glLineWidth(2.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 0.75f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	//const auto renderManager = SDK;
	for (Vector3D d : this->data)
	{
		//GLRenderBox(d.x + 0.7, d.y + 3.f, d.z, d.x + 1.2, d.y + 3.5, d.z + 0.5, 1.f, 1.f, 1.f, 0.2f);
		glColor4f(1.f, 1.f, 1.f, 1.f);
		drawOutlinedBox(BoundingBox{ d.x - .2, d.y - 0.05 + 3.4, d.z - .2, d.x + .2, d.y - 0.45 + 3.4, d.z + .2 });
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	if (Base::version != FORGE_1_18_1) glPopMatrix();


	if (Base::version != FORGE_1_18_1) glPopMatrix();
}

void ItemESP::RenderMenu()
{
	ImGui::BeginChild("ItemESP", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(46541, "Toggle ItemESP", this);
		//Menu::DoSliderStuff(45732343408, ", this->m_Radius->getPtr(), 0.1f, 15.f);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("ItemESP2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

void ItemESP::onUpdate(EventUpdate e)
{
	if (!this->getToggle())
		return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	std::vector<Vector3D> temp;
	List entitylist = SDK::GetInstance()->Minecraft->getTheWorld().GetLoadedEntityList();
	auto list = entitylist.toVector<CEntity>();
	for (CEntity entitys : list) {
		if (Java::GetInstance()->Env->IsInstanceOf(entitys.getInstance(), StrayCache::GetInstance()->entityItem_class)) {
			CEntityItem entity = CEntityItem(entitys.getInstance());
			double x = entity.GetPos().x - CommonData::getInstance()->renderPos.x;
			double y = entity.GetPos().y + 0.5 - (CommonData::getInstance()->renderPos.y);
			double z = entity.GetPos().z - CommonData::getInstance()->renderPos.z;
			temp.push_back(Vector3D(x, y, z));
		}
	}
	this->data = temp;
}

ItemESP::ItemESP() : AbstractModule("ItemESP", Category::VISUAL, "ItemESP.") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

std::vector<float> ItemESP::structToVector(const Matrix& matrix)
{
	std::vector<float> result;
	result.reserve(16); // 预留足够的空间以容纳结构体的成员

	result.push_back(matrix.m00);
	result.push_back(matrix.m01);
	result.push_back(matrix.m02);
	result.push_back(matrix.m03);

	result.push_back(matrix.m10);
	result.push_back(matrix.m11);
	result.push_back(matrix.m12);
	result.push_back(matrix.m13);

	result.push_back(matrix.m20);
	result.push_back(matrix.m21);
	result.push_back(matrix.m22);
	result.push_back(matrix.m23);

	result.push_back(matrix.m30);
	result.push_back(matrix.m31);
	result.push_back(matrix.m32);
	result.push_back(matrix.m33);

	return result;
}

void ItemESP::GLRenderBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(red, green, blue, alpha);

	glBegin(GL_QUADS);

	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ);

	glVertex3f(minX, minY, maxZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);

	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ);

	glVertex3f(minX, maxY, minZ);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	glEnd();

	glDisable(GL_BLEND);
}
