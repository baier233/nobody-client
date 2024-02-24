#include "BedESP.h"
#include <GL/GL.h>
void BedESP::RenderMenu()
{
	ImGui::BeginChild("BedESP", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(46541, "Toggle BedESP", this);
		//Menu::DoSliderStuff(45732343408, ", this->m_Radius->getPtr(), 0.1f, 15.f);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("BedESP2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}

void BedESP::onUpdate(EventUpdate e)
{
	if (!this->getToggle()) return;
	if (!CommonData::getInstance()->SanityCheck()) return;
	std::vector<Vector3> temp;
	List entityList = CommonData::getInstance()->loadedTitleEntities;
	if (entityList.isNULL()) return;
	auto list = entityList.toVector<CTileEntity>();
	for (CTileEntity& entity : list) {
		if (Java::Env->IsInstanceOf(entity.getInstance(), StrayCache::tileEntityBed_class)) {
			CTileEntityBed bed = CTileEntityBed(entity.getInstance());
			auto blockPos = bed.getPos();
			auto pos = blockPos.getPos();
			double x = pos.x - CommonData::getInstance()->renderPos.x;
			double y = pos.y - CommonData::getInstance()->renderPos.y + 3.4f;
			double z = pos.z - CommonData::getInstance()->renderPos.z;
			temp.push_back(Vector3(x, y, z));
		}
	}
	this->data = temp;

}

BedESP::BedESP() : AbstractModule("BedESP", Category::VISUAL, "BedESP.") {
	EventManager::getInstance().reg<EventUpdate>([this](auto&& PH1) { onUpdate(std::forward<decltype(PH1)>(PH1)); });
}

void BedESP::drawSelectionBoundingBox(BoundingBox boundingBox)
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.minZ);
	glVertex3f(boundingBox.maxX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.maxX, boundingBox.maxY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.minY, boundingBox.maxZ);
	glVertex3f(boundingBox.minX, boundingBox.maxY, boundingBox.maxZ);
	glEnd();
}

void BedESP::drawColorBox(BoundingBox axisalignedbb)
{
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.minX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.minZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.maxY, axisalignedbb.maxZ);
	glVertex3f(axisalignedbb.maxX, axisalignedbb.minY, axisalignedbb.maxZ);
	glEnd();
}


BedESP* BedESP::getInstance()
{
	static auto* inst = new BedESP();
	return inst;
}

void BedESP::onEnable()
{
}

void BedESP::onDisable()
{
}
std::vector<float> BedESP::structToVector(const Matrix& matrix)
{
	std::vector<float> result;
	result.reserve(16); 

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
void BedESP::RenderUpdate()
{
	if (!this->getToggle() || !CommonData::getInstance()->dataUpdated) return;
	if (Base::version != FORGE_1_18_1) glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->projection).data());
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(this->structToVector(CommonData::getInstance()->modelView).data());

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(2.0f);
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_LINE_SMOOTH);

	for (Vector3 d : this->data)
	{
		if (Base::version != FORGE_1_18_1) glPushMatrix();

		/*	glColor4d(2.0, 0.0, 0.0, 0.5);
			this->drawColorBox(BoundingBox(d.x, d.y, d.z, d.x + 1.f, d.y + 0.5, d.z + 1.f));*/

		glColor4d(102.0, 0.0, 153.0, 0.5);
		this->drawSelectionBoundingBox(BoundingBox(d.x, d.y, d.z, d.x + 1.f, d.y + 0.5, d.z + 1.f));

		if (Base::version != FORGE_1_18_1) glPopMatrix();
	}

	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	if (Base::version != FORGE_1_18_1) glPopMatrix();
}
