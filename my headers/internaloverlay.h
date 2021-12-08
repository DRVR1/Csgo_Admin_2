#pragma once 
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <conio.h>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "../libraries/include/imgui/imgui_impl_dx9.h"
#include "../libraries/include/imgui/imgui_impl_win32.h"

#include"hackbools.h"

#include "libraries/include/internalhook/detours.h"

#include <d3d9.h>
#include <d3dx9.h>


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

HINSTANCE DllHandle;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
endScene pEndScene;

LPD3DXFONT font;

WNDPROC oWndProc;

//configs ------------------------------------------------------------------------------------------------
const char targetName[] = "Counter-Strike: Global Offensive";

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
    
    if (hackbools::init) {
        HWND newhandler = FindWindowA(NULL, targetName);
        oWndProc = (WNDPROC)SetWindowLongPtr(newhandler, GWL_WNDPROC, (LONG_PTR)WndProc);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        
        ImGui_ImplWin32_Init(newhandler);
        ImGui_ImplDX9_Init(pDevice);

        ImGuiStyle* style = &ImGui::GetStyle();

        style->FramePadding = ImVec2(8, 4);
        style->WindowTitleAlign = ImVec2(0.5, 0.5);
        style->FramePadding = ImVec2(8, 6);
        style->Colors[ImGuiCol_TitleBg] = ImColor(255, 30, 30, 255);
        style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 30, 45, 255);
        style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 30, 45, 255);

        style->Colors[ImGuiCol_Button] = ImColor(255, 30, 45, 255);
        style->Colors[ImGuiCol_ButtonActive] = ImColor(240, 0, 0, 255);
        style->Colors[ImGuiCol_ButtonHovered] = ImColor(120, 30, 45, 255);

        style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 30, 45, 255);
        style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 30, 45, 255);
        style->Colors[ImGuiCol_ScrollbarBg] = ImColor(255, 30, 45, 255);

        ImGui::GetStyle().WindowRounding = 0.0f;// <- Set this on init or use ImGui::PushStyleVar()
        ImGui::GetStyle().ChildRounding = 0.0f;
        ImGui::GetStyle().FrameRounding = 0.0f;
        ImGui::GetStyle().GrabRounding = 0.0f;
        ImGui::GetStyle().PopupRounding = 0.0f;
        ImGui::GetStyle().ScrollbarRounding = 0.0f;

        ImGui::SetNextWindowSize(ImVec2(500, 500));

        CloseHandle(newhandler);
        hackbools::init = false;


    }


    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();




    if (hackbools::bmenuOpen) {

        ImGui::Begin("Csgo \"the admin\" alpha + 4", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        if (ImGui::Checkbox("Radar hack", &hackbools::radarHack)) {

        }

        if (ImGui::Checkbox("BunnyHop", &hackbools::bhHack)) {

        }

        if (ImGui::Checkbox("Flashbang anti blind", &hackbools::flashbangHack)) {

        }
        if (ImGui::Checkbox("tiggerbot", &hackbools::triggerbothack)) {
            
        }
        if (ImGui::Checkbox("aimbot", &hackbools::aimbothack)) {

        }
        if (ImGui::Checkbox("aimbot - aim team", &hackbools::targetTeam)) {

        }
        if (ImGui::Checkbox("aimbot - aim by sight", &hackbools::targetSight)) {

        }

    }

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
