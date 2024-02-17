#include "menu.h"
#include "../../main.h"

#include <Windows.h>
#include <string>
#include <vector>
#include <ShlObj.h>
#include <fstream>
#include <shellapi.h>

#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"

#include "../util/window/borderless.h"
#include "ImGuiUtils.h"
#include "../moduleManager/modules/visual/esp.h"
#include "../moduleManager/modules/visual/fullbright.h"
#include "../moduleManager/modules/visual/Xray.h"

#include "../moduleManager/modules/combat/aimAssist.h"
#include "../moduleManager/modules/combat/reach.h"
#include "../moduleManager/modules/combat/antibot.h"
#include "../moduleManager/modules/combat/teams.h"
#include "../moduleManager/modules/combat/velocity.h"
#include "../moduleManager/modules/combat/killaura.h"

#include "../moduleManager/modules/clicker/LClick.h"
#include "../moduleManager/modules/clicker/RClick.h"

#include "../moduleManager/modules/player/autotool.h"
#include "../moduleManager/modules/player/fastplace.h"
#include "../moduleManager/modules/player/scaffold.h"
#include "../moduleManager/modules/player/eagle.h"
#include "../moduleManager/modules/player/blink.h"

#include "../sdk/net/minecraft/client/Minecraft.h"

#include "../util/logger.h"
#include "../util/window/bind.hpp"

#include "../extension/config.h"

#include "../moduleManager/ModuleManager.h";
#include "Notification/NotificationManager.h"
#include "../../../ext/imgui/main.h"

inline static int style = 3;
inline static const char* styleList[4]{ "Dark", "Light", "Classic", "Gold" };

void set_config(INI ini) {

	for (HMOD Mod : ModuleManager::getInstance().getMods())
	{
		if (!Mod)
		{
			continue;
		}
		auto module = ToBaseModule(Mod);
		if (!module)
		{
			continue;
		}
		auto values = module->getValues();

		ini.create(module->getName());
		ini.select(module->getName());
		ini.set(module->getName() + " Enable", std::to_string(module->getToggle()));
		ini.set(module->getName() + " Key", std::to_string(module->getKey()));

		for (size_t i = 0; i < values.size(); i++) {
			switch (values[i].first)
			{
			case BoolType: {
				BoolValue* pValue = (BoolValue*)values[i].second;
				ini.set(pValue->getName(), std::to_string(pValue->getValue()));
				break;
			}
			case FloatType: {
				FloatValue* pValue = (FloatValue*)values[i].second;
				ini.set(pValue->getName(), std::to_string(pValue->getValue()));
				break;
			}
			case ListType: {
				ModeValue* pValue = (ModeValue*)values[i].second;
				ini.set(pValue->getName(), std::to_string(pValue->getValue()));
				break;
			}
			case ColorType: {
				ColorValue* pValue = (ColorValue*)values[i].second;
				float* colorArray = pValue->getValue();
				std::string serializedColor;
				for (size_t j = 0; j < 4; j++) {
					if (j > 0) {
						serializedColor += ",";
					}
					serializedColor += std::to_string(colorArray[j]);
				}
				ini.set(pValue->getName(), serializedColor);
				break;
			}
			default:
				break;
			}
		}
	}

	ini.save("config.ini");
	NotificationManager::getInstance().makeNotification("Config save successful", Type::SUCCESS);
}

void read_config(INI ini) {
	for (HMOD Mod : ModuleManager::getInstance().getMods())
	{
		if (!Mod)
		{
			continue;
		}
		auto module = ToBaseModule(Mod);
		if (!module)
		{
			continue;
		}
		auto values = module->getValues();
		ini.select(module->getName());
		module->setToggle(ini.getAs<bool>(module->getName() + " Enable"));
		module->setKeyCode(ini.getAs<int>(module->getName() + " Key"));
		for (size_t i = 0; i < values.size(); i++) {
			switch (values[i].first)
			{
			case BoolType: {
				BoolValue* pValue = (BoolValue*)values[i].second;
				*pValue->getValuePtr() = ini.getAs<bool>(pValue->getName());
				break;
			}
			case FloatType: {
				FloatValue* pValue = (FloatValue*)values[i].second;
				*pValue->getValuePtr() = ini.getAs<float>(pValue->getName());
				break;
			}
			case ListType: {
				ModeValue* pValue = (ModeValue*)values[i].second;
				*pValue->getValuePtr() = ini.getAs<int>(pValue->getName());
				break;
			}
			case ColorType: {
				ColorValue* pValue = (ColorValue*)values[i].second;
				float* colorArray = pValue->getValuePtr();
				break;
				std::string serializedColor = ini.getAs<std::string>(pValue->getName());
				std::istringstream iss(serializedColor);
				std::string token;

				for (int i = 0; i < 4; ++i) {
					if (std::getline(iss, token, ',')) {
						try {
							colorArray[i] = std::stof(token);
						}
						catch (const std::invalid_argument& e) {
							Logger::Log(e.what());
							break;
						}
					}
				}
				break;
			}
			default:
				break;
			}
		}
	}
	NotificationManager::getInstance().makeNotification("Config load successful", Type::SUCCESS);
}

// Function to list all files in a folder (platform-specific)
std::vector<std::string> ListFilesInFolder(const std::string& folderPath, const std::string& extension)
{
	std::vector<std::string> fileNames;

	std::string searchPath = folderPath + "\\*." + extension;
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				fileNames.push_back(findData.cFileName);
			}
		} while (FindNextFileA(hFind, &findData) != 0);

		FindClose(hFind);
	}

	return fileNames;
}

struct Block {
	float x;
	float y;
	float width;
	float height;
};

bool isBlockHovered(Block* block) {
	return ImGui::GetIO().MousePos.x > block->x &&
		ImGui::GetIO().MousePos.y > block->y &&
		ImGui::GetIO().MousePos.x < (block->x + block->width) &&
		ImGui::GetIO().MousePos.y < (block->y + block->height);
}

void drawBlockBoundingBox(Block* block) {
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(block->x, block->y), ImVec2(block->x + block->width, block->y + block->height), IM_COL32(255, 0, 0, 230));
}


int currentTab = -1;
int currentTab0 = 0;
int currentTab1 = 0;
int currentTab2 = 0;
int currentTab3 = 0;
int currentTab4 = 0;

#include "Image.h"
void Menu::RenderMenu()
{
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	CustomStyleColor();

	ImGui::SetNextWindowSize(ImVec2(802, 560));
	ImGui::PushFont(Manrope_Semmi_Font);
	ImGui::Begin(Menu::Title.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

	static const int numParticles = 115;
	static ImVec2 particlePositions[numParticles];
	static ImVec2 particleDistance;
	static ImVec2 particleVelocities[numParticles];
	static bool initialized = false;

	if (!initialized)
	{
		for (int i = 0; i < numParticles; ++i)
		{
			particlePositions[i] = ImVec2(
				ImGui::GetIO().DisplaySize.x * static_cast<float>(rand()) / RAND_MAX,
				ImGui::GetIO().DisplaySize.y * static_cast<float>(rand()) / RAND_MAX
			);

			particleVelocities[i] = ImVec2(
				static_cast<float>((rand() % 11) - 5),
				static_cast<float>((rand() % 11) - 5)
			);

		}

		initialized = true;
	}

	ImVec2 cursorPos = ImGui::GetIO().MousePos;
	for (int i = 0; i < numParticles; ++i)
	{
		// draw lines to particles
		for (int j = i + 1; j < numParticles; ++j)
		{
			float distance = std::hypotf(particlePositions[j].x - particlePositions[i].x, particlePositions[j].y - particlePositions[i].y);
			float opacity = 1.0f - (distance / 55.0f);  // opacity change

			if (opacity > 0.0f)
			{
				ImU32 lineColor = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, opacity));
				ImGui::GetBackgroundDrawList()->AddLine(particlePositions[i], particlePositions[j], lineColor, 2.0f);  // 设置线条粗细为2.0f
			}
		}

		// draw lines to cursor
		float distanceToCursor = std::hypotf(cursorPos.x - particlePositions[i].x, cursorPos.y - particlePositions[i].y);
		float opacityToCursor = 1.0f - (distanceToCursor / 52.0f);  // Adjust the divisor to control the opacity change

		if (opacityToCursor > 0.0f)
		{
			ImU32 lineColorToCursor = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, opacityToCursor));
			ImGui::GetBackgroundDrawList()->AddLine(cursorPos, particlePositions[i], lineColorToCursor, 2.0f);  // 设置线条粗细为2.0f
		}
	}

	// update and render particles
	float deltaTime = ImGui::GetIO().DeltaTime;
	for (int i = 0; i < numParticles; ++i)
	{
		particlePositions[i].x += particleVelocities[i].x * deltaTime;
		particlePositions[i].y += particleVelocities[i].y * deltaTime;

		// Stay in window
		if (particlePositions[i].x < 0)
			particlePositions[i].x = ImGui::GetIO().DisplaySize.x;
		else if (particlePositions[i].x > ImGui::GetIO().DisplaySize.x)
			particlePositions[i].x = 0;

		if (particlePositions[i].y < 0)
			particlePositions[i].y = ImGui::GetIO().DisplaySize.y;
		else if (particlePositions[i].y > ImGui::GetIO().DisplaySize.y)
			particlePositions[i].y = 0;

		ImU32 particleColour = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

		// render particles on the background
		ImGui::GetBackgroundDrawList()->AddCircleFilled(particlePositions[i], 3.0f, particleColour);  // 设置粒子的半径为3.0f
	}

	{
		const auto& p = ImGui::GetWindowPos();

		const ImVec2& region = ImGui::GetContentRegionMax();

		if (bg == nullptr) bg = glLoadTextureFromMemory(Background, sizeof(Background)); ImGui::GetWindowDrawList()->AddImageRounded(bg, ImVec2(p.x + 5, p.y + 5), ImVec2(p.x + region.x, p.y + region.y), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255) /*color*/, 0 /*rounding*/);

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 5, p.y + 5), ImVec2(p.x + 101, p.y + region.y), ImColor(11, 12, 13, 127), 10.f, ImDrawFlags_RoundCornersLeft);

		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + 101, p.y + 5), ImVec2(p.x + region.x, p.y + 86), ImColor(11, 12, 13, 127), 10.f, ImDrawFlags_RoundCornersTopRight);

		ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 101, p.y + 86), ImVec2(p.x + region.x, p.y + region.y), ImColor(52, 52, 52, 255), 10.f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersBottomRight);

		if (Logotip == nullptr) Logotip = glLoadTextureFromMemory(Logo, sizeof(Logo)); ImGui::GetWindowDrawList()->AddImageRounded(Logotip, ImVec2(p.x + 25, p.y + 25), ImVec2(p.x + 75, p.y + 70), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255) /*color*/, 0 /*rounding*/);

		ImGui::GetWindowDrawList()->AddRect(ImVec2(p.x + 5, p.y + 5), ImVec2(p.x + region.x, p.y + region.y), ImColor(52, 52, 52, 255), 10.f);

		static int page = 0;

		static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

		tab_alpha = ImClamp(tab_alpha + (5.f * ImGui::GetIO().DeltaTime * (page == active_tab ? 1.f : -1.f)), 0.f, 1.f);

		tab_add = ImClamp(tab_add + (std::round(350.f) * ImGui::GetIO().DeltaTime * (page == active_tab ? 1.f : -1.f)), 0.f, 1.f);

		if (tab_alpha == 0.f && tab_add == 0.f) active_tab = page;

		ImGui::SetCursorPos(ImVec2(28, 105));
		ImGui::BeginGroup();
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 25));

			if (ImGui::Tab("Settings", image::could, 0 == page, ImVec2(50, 50))) { page = 0; sub_tabs = 0; }

			if (ImGui::Tab("Player", image::exploits, 1 == page, ImVec2(50, 50))) { page = 1; sub_tabs = 0; }

			if (ImGui::Tab("Combat", image::aimbot, 2 == page, ImVec2(50, 50))) { page = 2; sub_tabs = 0; }

			if (ImGui::Tab("Clicker", image::drop, 3 == page, ImVec2(50, 50))) { page = 3; sub_tabs = 0; }

			if (ImGui::Tab("Visuals", image::visuals, 4 == page, ImVec2(50, 50))) { page = 4; sub_tabs = 0; }

			ImGui::PopStyleVar();
		}ImGui::EndGroup();


		//Begin Render Modules and values

		if (active_tab == 0)
		{
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);
			ImGui::SetCursorPos(ImVec2(121, 110));
			ImGui::BeginChild("Settings", ImVec2(320, 426), true);
			{
				//ImGui::Checkboxx("Detach", image::check, &Base::Running);
				ImGui::ColorEdit4("ESP Box", Esp::getInstance()->BoxColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("ESP Box Outline", Esp::getInstance()->OutlineColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("ESP Second Filled Box", Esp::getInstance()->SecondFilledBoxColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("ESP Circles", Esp::getInstance()->TestCirclesColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("ESP Text", Esp::getInstance()->TextColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
				ImGui::ColorEdit4("ESP Text Outline", Esp::getInstance()->TextOutlineColorValue->getValuePtr(), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			}
			ImGui::EndChild();
			ImGui::SameLine(0, 20);
			ImGui::BeginChild("Settings2", ImVec2(320, 426), true);
			{
				//ImGui::PushStyleVar(, 10.f);
				Block DetachBlock{};
				DetachBlock.x = -1;
				DetachBlock.y = 1;
				DetachBlock.width = 90;
				DetachBlock.height = 34;
				if (ImGui::Button("Detach", DetachBlock.x, DetachBlock.y, DetachBlock.width, DetachBlock.height)) {
					Base::Running = false;
				}
				//ImGui::SameLine();
				Block LoadConfigBlock{};
				LoadConfigBlock.x = 0;
				LoadConfigBlock.y = 1;
				LoadConfigBlock.width = 90;
				LoadConfigBlock.height = 34;
				if (ImGui::Button("Load Config", LoadConfigBlock.x, LoadConfigBlock.y, LoadConfigBlock.width, LoadConfigBlock.height)) {
					INI ini("config.ini", true);
					read_config(ini);
				}
				ImGui::SameLine();
				Block SaveConfigBlock{};
				SaveConfigBlock.x = 1;
				SaveConfigBlock.y = 1;
				SaveConfigBlock.width = 90;
				SaveConfigBlock.height = 34;
				if (ImGui::Button("Save Config", SaveConfigBlock.x, SaveConfigBlock.y, SaveConfigBlock.width, SaveConfigBlock.height)) {
					INI ini("config.ini", true);
					set_config(ini);
				}
				//ImGui::PopStyleColor();
			}
			ImGui::EndChild();
			ImGui::PopStyleVar();
		}

		if (active_tab == 1)
		{
			Block active_1{};
			active_1.x = p.x + 100;
			active_1.y = p.y + 5;
			active_1.width = 700.f;
			active_1.height = 85.f;
			ImGui::SetCursorPos(ImVec2(144, 38));
			ImGui::BeginGroup();
			{
				int currentModule = 0;
				int visibleModules = 0;  // 记录在范围内可见的模块数量
				float subTabWidth = 100.0f;  // 每个SubTab的宽度
				static float scrollOffset = 0.0f;  // 滚动偏移量

				// 计算可见的模块数量
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::PLAYER)
					{
						visibleModules++;
					}
				}

				// 根据滚轮左右移动SubTab
				if (ImGui::IsMouseHoveringRect(ImVec2(active_1.x, active_1.y), ImVec2(active_1.x + active_1.width, active_1.y + active_1.height)))
				{
					float scrollSpeed = 20.0f;  // 滚动速度

					// 左滚动
					if (ImGui::GetIO().MouseWheel < 0.0f)
					{
						scrollOffset += scrollSpeed;
						if (scrollOffset > visibleModules * subTabWidth)
						{
							scrollOffset = visibleModules * subTabWidth;
						}
					}
					// 右滚动
					else if (ImGui::GetIO().MouseWheel > 0.0f)
					{
						scrollOffset -= scrollSpeed;
						if (scrollOffset < 0.0f)
						{
							scrollOffset = 0.0f;
						}
					}
				}

				// 绘制可见的模块
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::PLAYER)
					{
						if (scrollOffset > currentModule * subTabWidth)
						{
							currentModule++;
							continue;
						}

						if (ImGui::SubTab(currentModule == sub_tabs, mod->getName().c_str()))
						{
							sub_tabs = currentModule;
						}

						currentModule++;
					}
				}
			}
			ImGui::EndGroup();

			ImGui::SetCursorPos(ImVec2(121, 110));
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);
			{
				int currentModule = 0;
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::PLAYER)
					{
						if (currentModule == sub_tabs)
						{
							mod->RenderMenu();
							break;
						}
						currentModule++;
					}
				}
				currentModule = 0;
			}
			ImGui::PopStyleVar();
		}

		if (active_tab == 2)
		{
			Block active_2{};
			active_2.x = p.x + 100;
			active_2.y = p.y + 5;
			active_2.width = 700.f;
			active_2.height = 85.f;
			ImGui::SetCursorPos(ImVec2(144, 38));
			ImGui::BeginGroup();
			{
				int currentModule = 0;
				int visibleModules = 0;  // 记录在范围内可见的模块数量
				float subTabWidth = 100.0f;  // 每个SubTab的宽度
				static float scrollOffset = 0.0f;  // 滚动偏移量

				// 计算可见的模块数量
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::COMBAT)
					{
						visibleModules++;
					}
				}

				// 根据滚轮左右移动SubTab
				if (ImGui::IsMouseHoveringRect(ImVec2(active_2.x, active_2.y), ImVec2(active_2.x + active_2.width, active_2.y + active_2.height)))
				{
					float scrollSpeed = 20.0f;  // 滚动速度

					// 左滚动
					if (ImGui::GetIO().MouseWheel < 0.0f)
					{
						scrollOffset += scrollSpeed;
						if (scrollOffset > visibleModules * subTabWidth)
						{
							scrollOffset = visibleModules * subTabWidth;
						}
					}
					// 右滚动
					else if (ImGui::GetIO().MouseWheel > 0.0f)
					{
						scrollOffset -= scrollSpeed;
						if (scrollOffset < 0.0f)
						{
							scrollOffset = 0.0f;
						}
					}
				}

				// 绘制可见的模块
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::COMBAT)
					{
						if (scrollOffset > currentModule * subTabWidth)
						{
							currentModule++;
							continue;
						}

						if (ImGui::SubTab(currentModule == sub_tabs, mod->getName().c_str()))
						{
							sub_tabs = currentModule;
						}

						currentModule++;
					}
				}
			}
			ImGui::EndGroup();


			ImGui::SetCursorPos(ImVec2(121, 110));
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);
			{
				int currentModule = 0;
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::COMBAT)
					{
						if (currentModule == sub_tabs)
						{
							mod->RenderMenu();
							break;
						}
						currentModule++;
					}
				}
				currentModule = 0;
			}
			ImGui::PopStyleVar();
		}

		if (active_tab == 3)
		{
			Block active_3{};
			active_3.x = p.x + 100;
			active_3.y = p.y + 5;
			active_3.width = 700.f;
			active_3.height = 85.f;
			ImGui::SetCursorPos(ImVec2(144, 38));
			ImGui::BeginGroup();
			{
				int currentModule = 0;
				int visibleModules = 0;  // 记录在范围内可见的模块数量
				float subTabWidth = 100.0f;  // 每个SubTab的宽度
				static float scrollOffset = 0.0f;  // 滚动偏移量

				// 计算可见的模块数量
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::CLICKER)
					{
						visibleModules++;
					}
				}

				// 根据滚轮左右移动SubTab
				if (ImGui::IsMouseHoveringRect(ImVec2(active_3.x, active_3.y), ImVec2(active_3.x + active_3.width, active_3.y + active_3.height)))
				{
					float scrollSpeed = 20.0f;  // 滚动速度

					// 左滚动
					if (ImGui::GetIO().MouseWheel < 0.0f)
					{
						scrollOffset += scrollSpeed;
						if (scrollOffset > visibleModules * subTabWidth)
						{
							scrollOffset = visibleModules * subTabWidth;
						}
					}
					// 右滚动
					else if (ImGui::GetIO().MouseWheel > 0.0f)
					{
						scrollOffset -= scrollSpeed;
						if (scrollOffset < 0.0f)
						{
							scrollOffset = 0.0f;
						}
					}
				}

				// 绘制可见的模块
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::CLICKER)
					{
						if (scrollOffset > currentModule * subTabWidth)
						{
							currentModule++;
							continue;
						}

						if (ImGui::SubTab(currentModule == sub_tabs, mod->getName().c_str()))
						{
							sub_tabs = currentModule;
						}

						currentModule++;
					}
				}
			}
			ImGui::EndGroup();



			ImGui::SetCursorPos(ImVec2(121, 110));
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);
			{
				int currentModule = 0;
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::CLICKER)
					{
						if (currentModule == sub_tabs)
						{
							mod->RenderMenu();
							break;
						}
						currentModule++;
					}
				}
				currentModule = 0;
			}
			ImGui::PopStyleVar();
		}

		if (active_tab == 4)
		{
			Block active_4{};
			active_4.x = p.x + 100;
			active_4.y = p.y + 5;
			active_4.width = 700.f;
			active_4.height = 85.f;
			ImGui::SetCursorPos(ImVec2(144, 38));
			ImGui::BeginGroup();
			{
				int currentModule = 0;
				int visibleModules = 0;  // 记录在范围内可见的模块数量
				float subTabWidth = 100.0f;  // 每个SubTab的宽度
				static float scrollOffset = 0.0f;  // 滚动偏移量

				// 计算可见的模块数量
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::VISUAL )
					{
						visibleModules++;
					}
				}

				// 根据滚轮左右移动SubTab
				if (ImGui::IsMouseHoveringRect(ImVec2(active_4.x, active_4.y), ImVec2(active_4.x + active_4.width, active_4.y + active_4.height)))
				{
					float scrollSpeed = 20.0f;  // 滚动速度

					// 左滚动
					if (ImGui::GetIO().MouseWheel < 0.0f)
					{
						scrollOffset += scrollSpeed;
						if (scrollOffset > visibleModules * subTabWidth)
						{
							scrollOffset = visibleModules * subTabWidth;
						}
					}
					// 右滚动
					else if (ImGui::GetIO().MouseWheel > 0.0f)
					{
						scrollOffset -= scrollSpeed;
						if (scrollOffset < 0.0f)
						{
							scrollOffset = 0.0f;
						}
					}
				}

				// 绘制可见的模块
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::VISUAL )
					{
						if (scrollOffset > currentModule * subTabWidth)
						{
							currentModule++;
							continue;
						}

						if (ImGui::SubTab(currentModule == sub_tabs, mod->getName().c_str()))
						{
							sub_tabs = currentModule;
						}

						currentModule++;
					}
				}
			}
			ImGui::EndGroup();


			ImGui::SetCursorPos(ImVec2(121, 110));
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style.Alpha);
			{
				int currentModule = 0;
				for (HMOD h : ModuleManager::getInstance().getMods())
				{
					auto mod = ToBaseModule(h);
					if (mod->getCategory() == Category::VISUAL)
					{
						if (currentModule == sub_tabs )
						{
							mod->RenderMenu();
							break;
						}
						currentModule++;
					}
				}
				currentModule = 0;
			}
			ImGui::PopStyleVar();
		}


		//End Render Modules and Values


	}
	ImGui::PopFont();


	ImGui::End();

	ImVec2 viewportPos = ImGui::GetMainViewport()->Pos;
	ImVec2 viewportSize = ImGui::GetMainViewport()->Size;
	ImVec2 textSize = ImGui::CalcTextSize(Base::BuildVersion.c_str());

	ImVec2 textPos(viewportPos.x + viewportSize.x - textSize.x + 25, viewportPos.y + viewportSize.y - textSize.y + 5);

	ImGui::GetBackgroundDrawList()->AddText(Benzin_Medium_Font, 15.f, textPos, ImGui::GetColorU32(ImGuiCol_Text), Base::BuildVersion.c_str());
}
