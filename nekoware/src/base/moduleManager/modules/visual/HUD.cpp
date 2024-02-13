#include "HUD.h"



HUD::HUD() : AbstractModule("HUD", Category::VISUAL, "HUD.") {
	setToggle(true);
}

HUD* HUD::getInstance()
{
	static HUD* inst = new HUD();
	return inst;
}

void HUD::onEnable()
{
	this->enabledMods.clear();
}

void HUD::onDisable()
{
	this->enabledMods.clear();
}

static float fontScale = 6.5f;
static float enabledListX = 0;
static float enabledListY = 0;
static float enabledModBgHeight = 25;
static float enabledModBgSideWidth = 6;
static float modNameOffsetX = 5;
static float modNameOffsetY = 4;
static float modNameFontSize = 20;

void HUD::RenderUpdate()
{
	if (!this->getToggle()) return;
	this->enabledMods.clear();
	ModuleManager::getInstance().getModule(true, &(this->enabledMods));
	std::stable_sort(this->enabledMods.begin(), this->enabledMods.end(), EnabledListSorter());
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	Block enabledListBlock{};
	enabledListBlock.x = enabledListX;
	enabledListBlock.y = enabledListY;
	enabledListBlock.width = 0;
	enabledListBlock.height = 0;

	float curYOffset = 0;
	for (HMOD _Mod : this->enabledMods) {
		AbstractModule* curMod = ToBaseModule(_Mod);

		// 使用ImGui的接口获取字符串在当前字体下的宽度
		//float modNameWidth = ImGui::CalcTextSize(curMod->getName().c_str()).x;
		float modNameWidth = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, curMod->getName().c_str()).x + 10;
		if (modNameWidth + enabledModBgSideWidth > enabledListBlock.width) enabledListBlock.width = modNameWidth + enabledModBgSideWidth;

		float curModX = enabledListX;
		float curModY = enabledListY + curYOffset;
		dl->AddRectFilled(ImVec2(curModX, curModY), ImVec2(curModX + modNameWidth, curModY + enabledModBgHeight), IM_COL32(17, 17, 27, 245));
		dl->AddRectFilled(ImVec2(curModX + modNameWidth, curModY), ImVec2(curModX + modNameWidth + enabledModBgSideWidth, curModY + enabledModBgHeight), IM_COL32(65, 90, 160, 255));
		dl->AddText(Menu::Font, modNameFontSize, ImVec2(curModX + modNameOffsetX, curModY + modNameOffsetY), IM_COL32(75, 106, 183, 250), curMod->getName().c_str());

		enabledListBlock.height += enabledModBgHeight;
		curYOffset += enabledModBgHeight;
	}
}

void HUD::RenderMenu()
{
}

bool EnabledListSorter::operator()(HMOD m1, HMOD m2)
{
	AbstractModule* mod1 = ToBaseModule(m1);
	AbstractModule* mod2 = ToBaseModule(m2);

	float mod1Width = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, mod1->getName().c_str()).x;
	float mod2Width = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, mod2->getName().c_str()).x;

	return mod1Width > mod2Width;
}

