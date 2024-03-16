#include "HUD.h"



HUD::HUD() : AbstractModule("HUD", Category::VISUAL, "HUD.") {
	setToggle(true);
	this->addValue(ListType, this->ArrayListMode);
}

HUD::ColorHSV HUD::RGB2HSV(ColorRGB in)
{

	ColorHSV         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0;
		out.h = NAN;                            // its now undefined
		return out;
	}
	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (in.g - in.b) / delta;        // between yellow & magenta
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}

HUD::ColorRGB HUD::HSV2RGB(ColorHSV in)
{

	double      hh, p, q, t, ff;
	long        i;
	ColorRGB    out;

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}

int HUD::rainbow(int delay, long timeOffset)
{
	struct timeb time;
	ftime(&time);

	double rainbow = ceil(((time.time * 1000 + time.millitm) + timeOffset) / 8 + delay / 20.0);

	ColorHSV rainbowHSV{};
	rainbowHSV.h = fmod(rainbow, 360.0);
	rainbowHSV.s = 1;
	rainbowHSV.v = 1;

	ColorRGB rainbowRGB{};
	rainbowRGB = HSV2RGB(rainbowHSV);
	rainbowRGB.r *= 255;
	rainbowRGB.g *= 255;
	rainbowRGB.b *= 255;

	return (0xFF << 24) | (static_cast<int>(rainbowRGB.r) << 16) | (static_cast<int>(rainbowRGB.g) << 8) | static_cast<int>(rainbowRGB.b);
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
struct Block {
	float x;
	float y;
	float width;
	float height;
};
std::string getCurrentTimeFormatted() {
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
	std::tm* timeinfo = std::localtime(&currentTime);
	std::ostringstream oss;
	oss << std::put_time(timeinfo, "%H:%M:%S");
	return oss.str();
}



void HUD::RenderUpdate()
{
	if (!this->getToggle()) return;
	this->enabledMods.clear();
	ModuleManager::getInstance().getModule(true, &(this->enabledMods));
	std::stable_sort(this->enabledMods.begin(), this->enabledMods.end(), EnabledListSorter());
	ImDrawList* dl = ImGui::GetForegroundDrawList();
	switch (this->ArrayListMode->getValue()) {
	case Old:
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
		break;
	}
	case New:
	{

		std::string watermark = " | " + getCurrentTimeFormatted() + " | " + std::to_string(static_cast<int>(std::round(ImGui::GetIO().Framerate)));
		dl->AddRectFilled(ImVec2(3, 4), ImVec2(Menu::nl14->CalcTextSizeA(20, FLT_MAX, 0.0f, watermark.c_str()).x + 81, Menu::nl14->CalcTextSizeA(20, FLT_MAX, 0.0f, watermark.c_str()).y + 12), ImColor(0.f, 0.f, 0.f, 180 / 255.f), 2.f);
		dl->AddText(Menu::nl14, 20.f, ImVec2(73, 8.5), -1, watermark.c_str());
		dl->AddText(Menu::nlBold14, 20.f, ImVec2(5.7F, 8), ImColor(3, 167, 243, 255), "NoBody");
		dl->AddText(Menu::nlBold14, 20.f, ImVec2(6.0F, 8.4f), -1, "NoBody");

		Block enabledListBlock{};
		enabledListBlock.x = enabledListX;
		enabledListBlock.y = enabledListY;
		enabledListBlock.width = 0;
		enabledListBlock.height = 0;
		int i = 0;
		float curYOffset = 0;
		for (HMOD _Mod : this->enabledMods) {
			AbstractModule* curMod = ToBaseModule(_Mod);
			++i;
			float modNameWidth = Menu::Font->CalcTextSizeA(modNameFontSize, FLT_MAX, 0.0f, curMod->getName().c_str()).x + 10;
			float curModX = ImGui::GetIO().DisplaySize.x - modNameWidth;
			float curModY = curYOffset;
			float currentTime = ImGui::GetTime();
			dl->AddRectFilled(ImVec2(curModX, curModY), ImVec2(curModX + modNameWidth, curModY + enabledModBgHeight), IM_COL32(0, 0, 0, 150));
			dl->AddText(Menu::Font, modNameFontSize, ImVec2(curModX + modNameOffsetX, curModY + modNameOffsetY), this->rainbow(100, 100 * i), curMod->getName().c_str());
			curYOffset += enabledModBgHeight;
		}
		break;
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

