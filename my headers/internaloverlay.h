#pragma once 
#include <stdio.h>
#include "imgui/imgui.h"
#include "../libraries/include/imgui/imgui_impl_dx9.h"
#include "../libraries/include/imgui/imgui_impl_win32.h"
#include"aimbot.h"
#include "libraries/include/internalhook/detours.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "helper2.h"
#include "anotherdraws.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

HINSTANCE DllHandle;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
endScene pEndScene;

LPD3DXFONT font;

WNDPROC oWndProc;



//configs ------------------------------------------------------------------------------------------------
const char targetName[] = "Counter-Strike: Global Offensive - Direct3D 9";

std::vector<const char*> bodypart = { "Head","Neck","Upper Body","Body","Stomach","Lower Body"};
//BOOLS ------------------------------------------------------------------------------------------------

bool box1 = 0, box2 = 0, box3 = 0, box4 = 0, box5 = 0, box6 = 0, box7 = 0, box8 = 0, box9 = 0, box10 = 0;

//BOOLS END------------------------------------------------------------------------------------------------
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   
    if (*(int*)(base::isMenuOpenBase + offset::isMenuOpen) != NULL || 0x0) {
        if (*(int*)(base::isMenuOpenBase + offset::isMenuOpen) == 4 || *(int*)(base::isMenuOpenBase + offset::isMenuOpen) == 3) {
            ImGuiIO& io = ImGui::GetIO();
            ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

            if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
                return true;
        }
    } return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);


}


HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) {

    csgo::gametickloopHacks();
    //DrawLine(pDevice, templine::a, templine::b, templine::c, D3DCOLOR_ARGB(0, 0, 0, 0));
    //DrawLine2(pDevice,templine::a, templine::b, templine::c, templine::d, templine::e, templine::thebool, D3DCOLOR_ARGB(0, 0, 0, 0));
    
    if (hackbools::init) {
        HWND newhandler = FindWindowA(NULL, targetName);
        oWndProc = (WNDPROC)SetWindowLongPtr(newhandler, GWL_WNDPROC, (LONG_PTR)WndProc);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        ImGui_ImplWin32_Init(newhandler);
        ImGui_ImplDX9_Init(pDevice);

        ImGuiStyle* style = &ImGui::GetStyle();



        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        
        style->WindowPadding = ImVec2(15, 15);
        style->WindowRounding = 5.0f;
        style->FramePadding = ImVec2(5, 5);
        style->FrameRounding = 4.0f;
        style->ItemSpacing = ImVec2(12, 8);
        style->ItemInnerSpacing = ImVec2(8, 6);
        style->IndentSpacing = 25.0f;
        style->ScrollbarSize = 15.0f;
        style->ScrollbarRounding = 9.0f;
        style->GrabMinSize = 5.0f;
        style->GrabRounding = 3.0f;

        style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
        style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
        style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
        style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
        style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
        style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);

        style->Colors[ImGuiCol_CheckMark] = ImVec4(0.184f, 0.407f, 1.00f, 1.00f);

        style->Colors[ImGuiCol_Tab] =       ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
        style->Colors[ImGuiCol_TabActive] = ImVec4(1.0f, 1.0f, 1.0f, 0.1f);
        style->Colors[ImGuiCol_TabActive] = ImVec4(0.1f, 0.1f, 1.0f, 0.5f);


        style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
        style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);

        style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);

        style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
        style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
        style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
        style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
        style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
        style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
        style->Colors[ImGuiCol_Border] = ImVec4(0, 0, 255, 1.00f);
       

        style->WindowMinSize = ImVec2(300,300); 

        CloseHandle(newhandler);
        hackbools::init = false;


    }


    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();






    if (hackbools::bmenuOpen) {

        ImGui::Begin("ghost assassin alpha", nullptr, ImGuiWindowFlags_NoCollapse);

        if (ImGui::BeginTabBar("options")) {
            if (ImGui::BeginTabItem("Aimbot")) {
                ImGui::Checkbox("Aimbot", &hackbools::aimbot::aimbothack);
                ImGui::Combo("Body part", &hackbools::aimbot::selectedbodypart, bodypart.data(), bodypart.size());
                ImGui::Checkbox("Target teammates",&hackbools::aimbot::targetTeam);
                ImGui::Checkbox("Yaw only", &hackbools::aimbot::yawonly);
                ImGui::Checkbox("Switch target after kill",&hackbools::aimbot::findnewtarget);
                ImGui::Checkbox("Smooth", &hackbools::aimbot::smoothaim);
                if (hackbools::aimbot::smoothaim) {
                    ImGui::SliderInt("Smooth speed", &hackbools::aimbot::newspeed, 0, 18);
                }
                ImGui::Checkbox("Draw target", &hackbools::aimbot::oscillation::drawOscillator);
                if (hackbools::aimbot::oscillation::drawOscillator) {
                    ImGui::ColorEdit4("Target color", hackbools::aimbot::oscillation::oscillatorcolor);
                    ImGui::SliderInt("Target size", &hackbools::aimbot::oscillation::antiOscillator, 1, 35);
                }
                ImGui::Checkbox("Use fov", &hackbools::aimbot::bfov);
                if (hackbools::aimbot::bfov) {
                    ImGui::Checkbox("DrawFov", &hackbools::aimbot::drawfov);
                    ImGui::SliderFloat("Fov", &hackbools::aimbot::fov, 1, hackbools::aimbot::fovAccuracy);
                    ImGui::SliderFloat("Fov range", &hackbools::aimbot::fovAccuracy, 1, 800);
                    ImGui::ColorEdit4("Fov color", hackbools::aimbot::fovcolor);
                }

                ImGui::Checkbox("Debug mode", &hackbools::aimbot::debug::debugmode);
                
                

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Misc")) {
                if (ImGui::Checkbox("Radar hack", &hackbools::radarHack)) {}
                if (ImGui::Checkbox("BunnyHop", &hackbools::bhHack)) {}
                if (ImGui::Checkbox("Anti-flashbang", &hackbools::flashbangHack)) {}
                if (ImGui::Checkbox("Auto accept", &hackbools::autoaccept)) {}


                ImGui::EndTabItem();
            }
        }

        if (ImGui::BeginTabItem("triggerbot")) {
            if (ImGui::Checkbox("Tiggerbot", &hackbools::triggerbot::triggerbothack)) {} 
            if (ImGui::Checkbox("Shoot teammates", &hackbools::triggerbot::targetTeam)) {}

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Visuals")) {
            ImGui::Checkbox("ESP line", &hackbools::visuals::esp::espline);
            if (hackbools::visuals::esp::espline) {
                ImGui::ColorEdit4("Esp line enemy", hackbools::visuals::esp::esplinecolorteam);
                ImGui::ColorEdit4("Esp line ally", hackbools::visuals::esp::esplinecolorenemy);
                ImGui::SliderFloat("Esp line tickness", &hackbools::visuals::esp::tickness, 1, 4);

            }
                
            ImGui::EndTabItem();
        }
    }
    if (hackbools::aimbot::debug::debugmode) {
        ImGui::Begin("debug", nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("World to screen:");
        ImGui::Text("Enemy X: %d", hackbools::aimbot::debug::gotoX);
        ImGui::Text("Enemy Y: %d", hackbools::aimbot::debug::gotoY);
        ImGui::Text("Enemy Z: %d", hackbools::aimbot::debug::gotoZ);
        ImGui::Spacing();
        ImGui::Text("Mouse X: %d", hackbools::aimbot::debug::mouseposX);
        ImGui::Text("Mouse Y: %d", hackbools::aimbot::debug::mouseposY);
        ImGui::Spacing();
        ImGui::Text("Iterator: %d", hackbools::aimbot::debug::iterator);
        ImGui::Text("reached: %d", hackbools::aimbot::debug::reached);
        ImGui::Text("Closest: %d", hackbools::aimbot::debug::closest);
        ImGui::Text("Health: %d", hackbools::aimbot::debug::health);
        ImGui::Text("Speed: %d", hackbools::aimbot::speed);
        ImGui::Text("Distance to Y center: %d", hackbools::aimbot::debug::distanceToY);



    }

    anotherDraws();


    ImGui::EndFrame();
    ImGui::Render();

    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    return pEndScene(pDevice); // call original endScene 
}


void hookEndScene() {
    IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION); // create IDirect3D9 object
    if (!pD3D)
        return;


    D3DPRESENT_PARAMETERS d3dparams = { 0 };
    d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dparams.hDeviceWindow = GetForegroundWindow();
    d3dparams.Windowed = true;

    IDirect3DDevice9* pDevice = nullptr;

    HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dparams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
    if (FAILED(result) || !pDevice) {
        pD3D->Release();
        return;
    }
    //if device creation worked out -> lets get the virtual table:
    void** vTable = *reinterpret_cast<void***>(pDevice);

    //now detour:

    pEndScene = (endScene)DetourFunction((PBYTE)vTable[42], (PBYTE)hookedEndScene);

   
    pDevice->Release();
    pD3D->Release();
}
