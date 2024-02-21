#include "HUD.h"



HUD::HUD() : AbstractModule("HUD", Category::VISUAL, "HUD.") {
	setToggle(true);
	this->addValue(ListType, this->ArrayListMode);
}

Color HUD::HSBtoRGB(float hue, float saturation, float brightness) {
	float red, green, blue;
	if (saturation == 0) {
		red = green = blue = brightness;
	}
	else {
		float huePrime = hue * 6;
		int hueSector = static_cast<int>(huePrime);
		float hueFraction = huePrime - hueSector;
		float p = brightness * (1 - saturation);
		float q = brightness * (1 - saturation * hueFraction);
		float t = brightness * (1 - saturation * (1 - hueFraction));

		switch (hueSector) {
		case 0:
			red = brightness;
			green = t;
			blue = p;
			break;
		case 1:
			red = q;
			green = brightness;
			blue = p;
			break;
		case 2:
			red = p;
			green = brightness;
			blue = t;
			break;
		case 3:
			red = p;
			green = q;
			blue = brightness;
			break;
		case 4:
			red = t;
			green = p;
			blue = brightness;
			break;
		default:
			red = brightness;
			green = p;
			blue = q;
			break;
		}
	}

	Color result;
	result.red = red;
	result.green = green;
	result.blue = blue;
	result.alpha = 1.0f;
	return result;
}

Color HUD::rainbow(float tick) {
	// 定义渐变的颜色值
	Color blueColor = { 0.0f, 0.0f, 1.0f, 1.0f };
	Color pinkColor = { 1.0f, 0.0f, 1.0f, 1.0f };
	Color whiteColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	// 计算渐变的权重
	float weight = std::sin(tick) * 0.5f + 0.5f;

	// 根据权重插值计算当前颜色
	Color currentColor;
	currentColor.red = blueColor.red * (1 - weight) + pinkColor.red * weight;
	currentColor.green = blueColor.green * (1 - weight) + pinkColor.green * weight;
	currentColor.blue = blueColor.blue * (1 - weight) + pinkColor.blue * weight;
	currentColor.alpha = blueColor.alpha * (1 - weight) + pinkColor.alpha * weight;

	return currentColor;
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
static float rainbowTick = 0.0f;
struct Block {
	float x;
	float y;
	float width;
	float height;
};

void HUD::RenderUpdate()
{
	if (!this->getToggle()) return;
	this->enabledMods.clear();
	ModuleManager::getInstance().getModule(true, &(this->enabledMods));
	std::stable_sort(this->enabledMods.begin(), this->enabledMods.end(), EnabledListSorter());
	ImDrawList* dl = ImGui::GetForegroundDrawList();

	switch (this->ArrayListMode->getValue())
	{
	case 1:
	{
		Block enabledListBlock{};
		enabledListBlock.x = enabledListX;
		enabledListBlock.y = enabledListY;
		enabledListBlock.width = 0;
		enabledListBlock.height = 0;

		float curYOffset = 0;
		for (HMOD _Mod : this->enabledMods) {
			AbstractModule* curMod = ToBaseModule(_Mod);

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

	default:
	{
		Block enabledListBlock{};
		enabledListBlock.x = enabledListX;
		enabledListBlock.y = enabledListY;
		enabledListBlock.width = 0;
		enabledListBlock.height = 0;

		float curYOffset = 0;
		for (HMOD _Mod : this->enabledMods) {
			AbstractModule* curMod = ToBaseModule(_Mod);
			float modNameWidth = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, curMod->getName().c_str()).x + 10;
			float curModX = ImGui::GetIO().DisplaySize.x - modNameWidth;
			float curModY = curYOffset;
			float currentTime = ImGui::GetTime();
			Color col = rainbow(currentTime);
			dl->AddText(Menu::Font, modNameFontSize, ImVec2(curModX + modNameOffsetX, curModY + modNameOffsetY), IM_COL32(col.red * 255, col.green * 255, col.blue * 255, 255), curMod->getName().c_str());
			curYOffset += enabledModBgHeight;
		}
	}
	}
}

void HUD::RenderMenu()
{
	//TODO: Add more options
	ImGui::BeginChild("HUD", ImVec2(320, 426), true);
	{
		Menu::DoToggleButtonStuff(696969, "Toggle HUD", this);
	}
	ImGui::EndChild();

	ImGui::SameLine(0, 20);

	ImGui::BeginChild("HUD2", ImVec2(320, 426), true);
	{
		int mode{};
		ImGui::Keybind("Click To Bind", image::keybind, &this->getKey(), &mode);
		ImGui::Combo("Style", this->ArrayListMode->getValuePtr(), this->ArrayListMode->getDescs(), 2);
	}
	ImGui::EndChild();
}

bool EnabledListSorter::operator()(HMOD m1, HMOD m2)
{
	AbstractModule* mod1 = ToBaseModule(m1);
	AbstractModule* mod2 = ToBaseModule(m2);

	float mod1Width = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, mod1->getName().c_str()).x;
	float mod2Width = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, mod2->getName().c_str()).x;

	return mod1Width > mod2Width;
}

