#include "ChestESP.h"
#include "../../../../../ext/minhook/minhook.h"
struct Object
{
	enum Type
	{
		Chest,
		LargeChest
	};

	Type m_type;

	glm::mat4 m_projection;
	glm::mat4 m_modelview;

	Object(Type type) : m_type{ type }
	{
		// Automatically fill it with the data of the current matrices
		glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(m_projection));
		glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(m_modelview));
	}
};

std::list<Object> objects;

// Pointers to original functions
decltype(&glOrtho) fn_glOrtho = glOrtho;
decltype(&glTranslatef) fn_glTranslatef = glTranslatef;

void drawBox(glm::vec4 color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
	{
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);

		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);

		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);

		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	}
	glEnd();
}

void doRender() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	// Setting up the context
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Transforming matrices
	for (auto& object : objects)
	{
		glm::mat4& modelview = object.m_modelview;
		glm::mat4& projection = object.m_projection;

		glm::vec4 color = glm::vec4(1.0f);
		glm::vec3 translate = glm::vec3(1.0f);
		glm::vec3 scale = glm::vec3(1.0f);

		switch (object.m_type)
		{
		case Object::Chest:
			color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			translate = glm::vec3(0.5f, 0.5f, 0.5f);
			scale = glm::vec3(0.5f, 0.5f, 0.5f);
			break;

		case Object::LargeChest:
			color = glm::vec4(0.91f, 0.87f, 0.42f, 1.0f);
			translate = glm::vec3(1.0f, 0.5f, 0.5f);
			scale = glm::vec3(1.0f, 0.5f, 0.5f);
			break;
		}

		modelview = glm::translate(modelview, translate);
		modelview = glm::scale(modelview, scale);

		// Setup matrices
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(projection));

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(glm::value_ptr(modelview));

		// Drawing box
		drawBox(color);
	}

	objects.clear();

	// Restoring settings (context and matrix)
	glPopAttrib();
	glPopMatrix();
}

// Hooked glOrtho function
void WINAPI hk_glOrtho(double left, double right, double bottom, double top, double zNear, double zFar)
{

	if (ChestESP::getInstance()->bypassObsValue->getValue())
	{
		return fn_glOrtho(left, right, bottom, top, zNear, zFar);

	}
	// Probably game preparing to draw inventory
	if (zNear == 1000.0 and zFar == 3000.0)
	{
		// Saving settings (context and current matrix)
		doRender();
		
	}

	// Calling the original function
	fn_glOrtho(left, right, bottom, top, zNear, zFar);
}
// Hooked glTranslatef function
void WINAPI hk_glTranslatef(float x, float y, float z)
{

	// Probably game preparing to draw chest
	if (x == 0.5f and y == 0.4375f and z == 0.9375f)
		objects.push_back(Object::Chest);

	// Probably game preparing to draw large chest
	if (x == 1.0f and y == 0.4375f and z == 0.9375f)
		objects.push_back(Object::LargeChest);

	// Calling the original function
	fn_glTranslatef(x, y, z);
}
ChestESP::ChestESP() : AbstractModule("ChestESP", Category::VISUAL, "show all Chest.") {
	this->addValue(BoolType,this->bypassObsValue);
	MH_CreateHook(glOrtho, hk_glOrtho, reinterpret_cast<void**>(&fn_glOrtho));
	//MH_CreateHook(glScalef, hk_glScalef, reinterpret_cast<void**>(&fn_glScalef));
	MH_CreateHook(glTranslatef, hk_glTranslatef, reinterpret_cast<void**>(&fn_glTranslatef));
}
ChestESP* ChestESP::getInstance()
{
	static ChestESP* inst = new ChestESP();
	return inst;
}

void ChestESP::onEnable()
{
	MH_EnableHook(glOrtho);
	MH_EnableHook(glTranslatef);
}

void ChestESP::onDisable()
{
	MH_DisableHook(glOrtho);
	MH_DisableHook(glTranslatef);
}

void ChestESP::RenderUpdate()
{
	if (!this->getToggle())
		return;
	if (!this->bypassObsValue->getValue())
		return;

	doRender();
}

void ChestESP::RenderMenu()
{
	ImGui::BeginChild("ChestESP", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(46541, "Toggle ChestESP", this);
		Menu::DoToggleButtonStuff(46541, "Obs Bypass", this->bypassObsValue->getValuePtr());
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("ChestESP2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}
