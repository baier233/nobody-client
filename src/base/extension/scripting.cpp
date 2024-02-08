#include "../../lua/lua.hpp"
#include <iostream>
#include "scripting.hpp"
#include "../menu/menu.h"
#include <ShlObj.h>
#include "../sdk/sdk.h"

// The variable to be controlled from Lua
//bool skidwareText = false;

int luaEnableOnGround(lua_State* L) {
    SDK::Minecraft->thePlayer->setOnGround(true);
    return 0;
}

int luaDisableOnGround(lua_State* L) {
    SDK::Minecraft->thePlayer->setOnGround(false);
    return 0;
}

int luaGetOnGround(lua_State* L) {
    lua_pushboolean(L, SDK::Minecraft->thePlayer->isOnGround());
    return 1;
}

// C++ function to enable the variable
int luaEnableVariable(lua_State* L) {
    scripting::skidwareText = true;
    return 0;
}

// C++ function to disable the variable
int luaDisableVariable(lua_State* L) {
    scripting::skidwareText = false;
    return 0;
}

// C++ function to get the variable's status
int luaGetVariableStatus(lua_State* L) {
    lua_pushboolean(L, scripting::skidwareText);
    return 1;
}

int luaLoadAndExecuteScript(lua_State* L) {
    const char* filename = lua_tostring(L, 1); // Get the Lua script filename from the Lua stack
    if (filename && luaL_loadfile(L, filename) == LUA_OK) {
        int status = lua_pcall(L, 0, 0, 0);
        if (status != LUA_OK) {
            std::cout << "Error executing Lua script: " << lua_tostring(L, -1) << std::endl;
        }
    }
    else {
        std::cout << "Error loading Lua script: " << lua_tostring(L, -1) << std::endl;
    }
    return 0;
}

// Function to get the ProgramData folder path
std::string GetProgramDataFolderPath() {
    char programDataPath[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, programDataPath) == S_OK) {
        return programDataPath;
    }
    return ""; // Return an empty string if the function fails to get the path
}


void scripting::luaThing(lua_State* L, const std::string& scriptFilename) {

    // Register the C++ functions in the Lua environment
    lua_register(L, "enableVariable", luaEnableVariable);
    lua_register(L, "disableVariable", luaDisableVariable);
    lua_register(L, "getVariableStatus", luaGetVariableStatus);
    lua_register(L, "loadAndExecuteScript", luaLoadAndExecuteScript);

    // Player
    lua_register(L, "enableOnGround", luaEnableOnGround);
    lua_register(L, "disableOnGround", luaDisableOnGround);
    lua_register(L, "getOnGround", luaGetOnGround);

    std::string fullPath = "C:\\" + scriptFilename;

    // maybe luaL_dofile instead of luaL_loadfile?
    // result: immediate crash.
    if (luaL_loadfile(L, fullPath.c_str()) || lua_pcall(L, 0, 0, 0)) {
        std::cout << "Error loading and executing Lua script: " << lua_tostring(L, -1) << std::endl;
    }

    // Your Lua script has been loaded and executed successfully
    // You can now interact with the Lua environment if needed

    //return 0;
}