#pragma once
#include <Windows.h>
#include "helper.h"
#include "hackbools.h"


namespace csgo {
    void loopHacks() {
        //activate cheats and check if in game menu is open
        //========================|MENU TOGGLER|================================
        if (*(int*)(base::isMenuOpenBase + offset::isMenuOpen) != NULL || 0x0) {
            hackbools::menuOpen = *(int*)(base::isMenuOpenBase + offset::isMenuOpen);
            if (hackbools::menuOpen == 2) {//playing
                hackbools::bmenuOpen = false;
            }
            if (hackbools::menuOpen == 4) {//pause menu
                hackbools::bmenuOpen = true;
            }

        }
        if (hackbools::menuOpen == 3) { //main menu
            if (GetAsyncKeyState(0x2D) & 1) {
                if (hackbools::bmenuOpen) {
                    hackbools::bmenuOpen = false;
                }
                else {
                    hackbools::bmenuOpen = true;
                }

            }
        }

        //========================|RADAR HACK|================================
        if (hackbools::radarHack) { action::radarHack(); }

        //========================|bunny hop|================================
        if (hackbools::bhHack) { action::bunnyJump(); }

        //========================|flashbang|================================
        if (hackbools::flashbangHack) {
            if (*(DWORD*)pointer::localPlayerptr != NULL || 0x0) {
                *(FLOAT*)((*(DWORD*)pointer::localPlayerptr) + offset::flashbangHex) = 0;
            }
        }

        if (!hackbools::flashbangHack) {
            if (*(DWORD*)pointer::localPlayerptr != NULL || 0x0) {
             *(FLOAT*)((*(DWORD*)pointer::localPlayerptr) + offset::flashbangHex) = 255;
            }
        }
        //========================|triggerbot|================================
        if (hackbools::triggerbothack) { action::triggerBot(); }
        //========================|aimbot|================================
        if (hackbools::aimbothack) { action::aimbotheader(); }
    }
}