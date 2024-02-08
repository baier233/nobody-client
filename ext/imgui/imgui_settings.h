#pragma once
#pragma once

#include "imgui.h"

namespace c {


        inline ImVec4 rect = ImColor(52, 52, 52, 255);
        inline ImVec4 line;
        inline ImVec4 line_tab = ImColor(78, 78, 78, 58);
        inline ImVec4 text_active = ImColor(255,255,255,255);
        inline ImVec4 active_sub = ImColor(172, 187, 120, 255);
        inline ImVec4 text_inactive = ImColor(255, 255, 255, 127);
        inline ImVec4 background = ImColor(11, 12, 13, 255);
        inline ImVec4 background_sun = ImColor(11, 12, 13, 127);
        inline ImVec4 background_1 = ImColor(11, 11, 11, 255);
        inline ImVec4 cursor = ImColor(255, 255, 255, 255);
        inline ImVec4 input_bg = ImColor(19, 19, 19, 255);
}
namespace settings {
   
    inline float animation_speed = 6.f;
}
