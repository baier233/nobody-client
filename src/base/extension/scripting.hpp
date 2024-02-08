#pragma once

#include "../../lua/lua.hpp"

struct scripting
{
	static void luaThing(lua_State* L, const std::string& scriptFilename);
	static bool skidwareText;
	static bool loadScript;
};

