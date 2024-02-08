#include "Chams.h"
#include "../../../../../ext/minhook/minhook.h"


// Pointers to original functions
decltype(&glScalef) fn_glScalef = glScalef;
void hk_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
	if (x == 0.9375) {
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0F, -2000000.f);
	}
	else {
		glPolygonOffset(1.0F, 2000000.f);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	fn_glScalef(x, y, z);
}

Chams::Chams() : AbstractModule("Chams", Category::VISUAL, "Chams.") {
	MH_CreateHook(glScalef, hk_glScalef, reinterpret_cast<void**>(&fn_glScalef));
}
Chams* Chams::getInstance()
{
	static Chams* inst = new Chams();
	return inst;
}

void Chams::onEnable()
{
	MH_EnableHook(glScalef);
}

void Chams::onDisable()
{
	MH_DisableHook(glScalef);
}

void Chams::RenderUpdate()
{
}

void Chams::RenderMenu()
{
	ImGui::BeginChild("Chams", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(465419, "Toggle Chams", this);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("Chams2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
	}
	ImGui::EndChild();
}
