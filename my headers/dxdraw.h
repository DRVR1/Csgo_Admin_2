#pragma once
#include "internaloverlay.h"

void DrawLine(LPDIRECT3DDEVICE9 Device_Interface, int bx, int by, int bw, D3DCOLOR COLOR)
{
    D3DRECT rec;
    rec.x1 = bx - bw;//makes line longer/shorter going lef
    rec.y1 = by; // base y
    rec.x2 = bx + bw;//makes line longer/shorter going right
    rec.y2 = by + 1;//makes line one pixel tall
    Device_Interface->Clear(1, &rec, D3DCLEAR_TARGET, COLOR, 0, 0);

}

void DrawLine2(LPDIRECT3DDEVICE9 pDevice,float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color)
{
    ID3DXLine* m_Line;

    D3DXCreateLine(pDevice, &m_Line);
    D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
    m_Line->SetWidth(width);
    if (antialias) m_Line->SetAntialias(1);
    m_Line->Begin();
    m_Line->Draw(line, 2, color);
    m_Line->End();
    m_Line->Release();
}

void drawcircle(int x, int y, int radius){
        ImDrawList*  draw = ImGui::GetBackgroundDrawList();
        draw->AddCircle(ImVec2(x,y), radius, IM_COL32(255,255,0,255), 100, 1.0f);
        ImGui::End();
}

void drawline(int x, int y, int z, int w, float e) {
    ImDrawList* draw = ImGui::GetBackgroundDrawList();
    draw->AddLine(ImVec2(x, y), ImVec2(z, w), IM_COL32(255, 255, 0, 255), e);
    ImGui::End();
}

void anotherDraws() {

    if (hackbools::aimbot::drawfov) {
        auto draw = ImGui::GetBackgroundDrawList();
        ImVec4 newfovcolor; //(first create a vector4 with the float colors then convert that vector into ImU32)
        newfovcolor.x = hackbools::aimbot::fovcolor[0];
        newfovcolor.y = hackbools::aimbot::fovcolor[1];
        newfovcolor.z = hackbools::aimbot::fovcolor[2];
        newfovcolor.w = hackbools::aimbot::fovcolor[3];
        ImU32 newfovcolor2 = ImGui::ColorConvertFloat4ToU32(newfovcolor);
        draw->AddCircle(ImVec2(xhairx, xhairy), hackbools::aimbot::fov, newfovcolor2, 100, 1.0f);
        ImGui::End();
    }
    if (hackbools::aimbot::oscillation::drawOscillator && hackbools::aimbot::oscillation::canDraw) {
        drawcircle(hackbools::aimbot::debug::gotoX, hackbools::aimbot::debug::gotoY, hackbools::aimbot::oscillation::antiOscillator);
    }

}