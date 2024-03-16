#pragma once
#include "imgui_internal.h"

namespace image
{
	inline ImTextureID aimbot = nullptr;
	inline ImTextureID no_aimbot = nullptr;
	inline ImTextureID visuals = nullptr;
	inline ImTextureID drop = nullptr;
	inline ImTextureID could = nullptr;
	inline ImTextureID exploits = nullptr;

	inline ImTextureID keybind = nullptr;
	inline ImTextureID input = nullptr;
	inline ImTextureID check = nullptr;
	inline ImTextureID arrows = nullptr;

	inline ImTextureID iconInfo = nullptr;
	inline ImTextureID iconErr = nullptr;
	inline ImTextureID iconSucc = nullptr;
	inline ImTextureID iconWarn = nullptr;

}

inline ImTextureID bg = nullptr;
inline ImTextureID Logotip = nullptr;
inline ImTextureID bg_cs = nullptr;
inline void CustomStyleColor()
{
	ImGuiStyle& s = ImGui::GetStyle();
	ImGuiContext& g = *GImGui;

	s.Colors[ImGuiCol_PopupBg] = ImColor(11, 12, 13, 255);
	s.Colors[ImGuiCol_ChildBg] = ImColor(11, 12, 13, 127);
	s.Colors[ImGuiCol_Border] = ImColor(52, 52, 52, 255);
	/*s.Colors[ImGuiCol_Button] = ImColor(172, 187, 120, 255);
	s.Colors[ImGuiCol_ButtonActive] = ImColor(172, 187, 120, 255);
	s.Colors[ImGuiCol_ButtonHovered] = ImColor(172, 187, 120, 255);*/
	s.ChildRounding = 10.f;
	s.WindowRounding = 10.f;
	//s.FrameRounding = 5.f;
	s.WindowPadding = ImVec2(0, 0);
}
inline ImFont* Manrope_Semmi_Font = nullptr;
inline ImFont* Benzin_Medium_Font = nullptr;
inline ImFont* Harmony_Regular_Font = nullptr;
inline ImFont* Harmony_Bold_Font = nullptr;
inline int sub_tabs = 0;

