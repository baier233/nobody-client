#include "Chams.h"
#include "../../../../../ext/minhook/minhook.h"


// Pointers to original functions
decltype(&glScalef) fn_glScalef = glScalef;
void hk_glScalef(GLfloat x, GLfloat y, GLfloat z)
{
	if (x == 0.9375)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, -1100000.0f);
		switch (Chams::getInstance()->mode->getValue()) {
		case 1:
			glDisable(GL_TEXTURE_2D);
			glColor3f(Chams::getInstance()->ChamsColor->getValue()[0], Chams::getInstance()->ChamsColor->getValue()[1], Chams::getInstance()->ChamsColor->getValue()[2]);
			glDisable(GL_LIGHTING);
			break;
		default:
			glLineWidth(3.f);

			glPolygonMode(1032, 6913);
			glEnable(10754);
			glDepthRange(0.0, 0.01);
			glDisable(3553);
			glEnable(2848);
			glHint(3154, 4354);
			break;
		}


	}
	else {
		if (x == 0.00390625 || x == 0.666667 || x == 0.0104167 || x == -0.0266667)
		{
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1100000.0f);

			switch (Chams::getInstance()->mode->getValue()) {
			case 1:
				glEnable(GL_TEXTURE_2D);
				glColor4f(1, 1, 1, 1);
				break;
			default:
				glPolygonMode(1032, 6914);
				glDepthRange(0.0, 1.0);
				glEnable(3553);
				glDisable(2848);
				break;
			}
		}
		else {
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1100000.0f);

			switch (Chams::getInstance()->mode->getValue()) {
			case 1:
				glEnable(GL_TEXTURE_2D);
				glColor4f(1, 1, 1, 1);
				break;
			default:
				glPolygonMode(1032, 6914);
				glDepthRange(0.0, 1.0);
				glEnable(3553);
				glDisable(2848);
				break;
			}
		}

		if (x > 0.f)
		{
			glDisable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0f, 1100000.0f);
			switch (Chams::getInstance()->mode->getValue()) {
			case 1:
				glEnable(GL_TEXTURE_2D);
				glColor4f(1, 1, 1, 1);
				break;
			default:
				glPolygonMode(1032, 6914);
				glDepthRange(0.0, 1.0);
				glEnable(3553);
				glDisable(2848);
				break;
			}

		}

	}

	fn_glScalef(x, y, z);
}

Chams::Chams() : AbstractModule("Chams", Category::VISUAL, "Chams.") {
	MH_CreateHook(glScalef, hk_glScalef, reinterpret_cast<void**>(&fn_glScalef));
	this->addValue(ListType, mode);
	this->addValue(ColorType, ChamsColor);
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
		ImGui::Combo("Chams Draw Mode", this->mode->getValuePtr(), this->mode->getDescs(), 2);
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
