#pragma once 
#include <stdio.h>
#include "imgui/imgui.h"
#include "../libraries/include/imgui/imgui_impl_dx9.h"
#include "../libraries/include/imgui/imgui_impl_win32.h"
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



void drawcircle(int x, int y, int radius, ImU32 color){
        ImDrawList*  draw = ImGui::GetBackgroundDrawList();
        draw->AddCircle(ImVec2(x,y), radius, color, 100, 1.0f);
        ImGui::End();
}

void drawline(int x, int y, int z, int w, float e, ImU32 color) {
    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    draw->AddLine(ImVec2(x, y), ImVec2(z, w), color, e);
    ImGui::End();
}

