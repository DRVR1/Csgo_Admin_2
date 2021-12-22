#pragma once
#include "dxdraw.h"
#include "hackbools.h"
#include "worldtoscreen.h"

void anotherDraws() {
    //========================|fov|================================
    if (hackbools::aimbot::drawfov) {
        auto draw = ImGui::GetBackgroundDrawList();
        ImVec4 newfovcolor; 
        newfovcolor.x = hackbools::aimbot::fovcolor[0];
        newfovcolor.y = hackbools::aimbot::fovcolor[1];
        newfovcolor.z = hackbools::aimbot::fovcolor[2];
        newfovcolor.w = hackbools::aimbot::fovcolor[3];
        ImU32 newfovcolor2 = ImGui::ColorConvertFloat4ToU32(newfovcolor);
        drawcircle(xhairx, xhairy, hackbools::aimbot::fov, newfovcolor2);
        ImGui::End();
    }
    //========================|target circle|================================
    if (hackbools::aimbot::oscillation::drawOscillator && hackbools::aimbot::oscillation::canDraw && hackbools::aimbot::aimbothack) {
        ImVec4 newfovcolor;
        newfovcolor.x = hackbools::aimbot::oscillation::oscillatorcolor[0];
        newfovcolor.y = hackbools::aimbot::oscillation::oscillatorcolor[1];
        newfovcolor.z = hackbools::aimbot::oscillation::oscillatorcolor[2];
        newfovcolor.w = hackbools::aimbot::oscillation::oscillatorcolor[3];
        ImU32 newfovcolor2 = ImGui::ColorConvertFloat4ToU32(newfovcolor);
        drawcircle(hackbools::aimbot::debug::gotoX, hackbools::aimbot::debug::gotoY, hackbools::aimbot::oscillation::antiOscillator, newfovcolor2);
    }

    //========================|esp line|================================
    if (hackbools::visuals::esp::espline) {
        espline();
    }
}