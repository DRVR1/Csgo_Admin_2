#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>


#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <conio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> 

#include "my headers/signature.h"
#include "my headers/Offsets.h"
#include "my headers/helper.h"
#include "my headers/setOffets.h"
#include "my headers/internaloverlay.h"
#include "my headers/aimbot.h"

#include "libraries/include/internalhook/detours.h"
#include "my headers/helper2.h"

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")






DWORD WINAPI MainActivity(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

            bool stablished = false;
            stablished = stablishOffsets();












            //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)FindClosestEnemythread, hModule, NULL, NULL);
            //FreeConsole();
            //fclose(f);
            //while (1) {
            //    aimbot();
            //    if (GetAsyncKeyState(0x39) & 1) {
            //        break;
            //    }
            //}
            //stablished = false;



















            if (stablished) {
                FreeConsole();
                fclose(f);
                hookEndScene();
                while (1) {
                    csgo::loopHacks();
                    if (GetAsyncKeyState(0x39)) {
                        DetourRemove((PBYTE)pEndScene, (PBYTE)hookedEndScene);
                        break;
                    }
                }
            }
            if (!stablished){
                printf("Unable to update offsets, wait for an update\n");
                system("pause");
            }
      
            
    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);


    
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainActivity, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

