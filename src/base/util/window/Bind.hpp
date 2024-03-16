#pragma once

#include <unordered_map>
#include <Windows.h>
#include <string>
#include "../xorstr.h"
#include "../../../../ext/imgui/imgui.h"

namespace keybind
{
	inline std::string get_key_name_by_id(int id)
	{
		static std::unordered_map< int, std::string > key_names =
		{
			{ 0, xorstr("None") },
			{ VK_LBUTTON, xorstr("Mouse 1") },
			{ VK_RBUTTON, xorstr("Mouse 2") },
			{ VK_MBUTTON, xorstr("Mouse 3") },
			{ VK_XBUTTON1, xorstr("Mouse 4") },
			{ VK_XBUTTON2, xorstr("Mouse 5") },
			{ VK_BACK, xorstr("Back") },
			{ VK_TAB, xorstr("Tab") },
			{ VK_CLEAR, xorstr("Clear") },
			{ VK_RETURN, xorstr("Enter") },
			{ VK_SHIFT, xorstr("Shift") },
			{ VK_CONTROL, xorstr("Ctrl") },
			{ VK_MENU, xorstr("Alt") },
			{ VK_PAUSE, xorstr("Pause") },
			{ VK_CAPITAL, xorstr("Caps Lock") },
			{ VK_ESCAPE, xorstr("Escape") },
			{ VK_SPACE, xorstr("Space") },
			{ VK_PRIOR, xorstr("Page Up") },
			{ VK_NEXT, xorstr("Page Down") },
			{ VK_END, xorstr("End") },
			{ VK_HOME, xorstr("Home") },
			{ VK_LEFT, xorstr("Left Key") },
			{ VK_UP, xorstr("Up Key") },
			{ VK_RIGHT, xorstr("Right Key") },
			{ VK_DOWN, xorstr("Down Key") },
			{ VK_SELECT, xorstr("Select") },
			{ VK_PRINT, xorstr("Print Screen") },
			{ VK_INSERT, xorstr("Insert") },
			{ VK_DELETE, xorstr("Delete") },
			{ VK_HELP, xorstr("Help") },
			{ VK_SLEEP, xorstr("Sleep") },
			{ VK_MULTIPLY, xorstr("*") },
			{ VK_ADD, xorstr("+") },
			{ VK_SUBTRACT, xorstr("-") },
			{ VK_DECIMAL, xorstr(".") },
			{ VK_DIVIDE, xorstr("/") },
			{ VK_NUMLOCK, xorstr("Num Lock") },
			{ VK_SCROLL, xorstr("Scroll") },
			{ VK_LSHIFT, xorstr("Left Shift") },
			{ VK_RSHIFT, xorstr("Right Shift") },
			{ VK_LCONTROL, xorstr("Left Ctrl") },
			{ VK_RCONTROL, xorstr("Right Ctrl") },
			{ VK_LMENU, xorstr("Left Alt") },
			{ VK_RMENU, xorstr("Right Alt") },
		};

		if (id >= 0x30 && id <= 0x5A)
			return std::string(1, (char)id);

		if (id >= 0x60 && id <= 0x69)
			return xorstr("Num ") + std::to_string(id - 0x60);

		if (id >= 0x70 && id <= 0x87)
			return xorstr("F") + std::to_string((id - 0x70) + 1);

		return key_names[id];
	}

	void key_bind(int& key, int width, int height)
	{
		static auto b_get = false;
		static std::string sz_text = xorstr("click to bind");

		if (ImGui::Button(sz_text.c_str(), ImVec2(static_cast<float>(width), static_cast<float>(height))))
			b_get = true;

		if (b_get)
		{
			for (auto i = 1; i < 256; i++)
			{
				if (GetAsyncKeyState(i) & 0x8000)
				{
					if (i != 12)
					{
						key = i == VK_ESCAPE ? 0 : i;
						b_get = false;
					}
				}
			}
			sz_text = xorstr("press a key");
		}
		else if (!b_get && key == 0)
			sz_text = xorstr("click to bind");
		else if (!b_get && key != 0)
			sz_text = xorstr("bound to: ") + get_key_name_by_id(key);
	}
}