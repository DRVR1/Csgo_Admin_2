#pragma once
#include <Windows.h>
#include "helper.h"
#include "hackbools.h"


namespace csgo {
    void loopHacks() {
        //activate cheats and check if in game menu is open
        //========================|MENU TOGGLER|================================
            hackbools::Instance = localplayer::status::instance();
            if (hackbools::Instance == 2) {//playing
            hackbools::bmenuOpen = false;
            }
            if (hackbools::Instance == 4) {//pause menu
                if (hackbools::shouldopen) {
                    hackbools::bmenuOpen = true;
                }
                else {
                    hackbools::bmenuOpen = false;
                }
            }
            if (hackbools::Instance == 3) {//main menu
                if (hackbools::shouldopen) {
                    hackbools::bmenuOpen = true;
                }else{
                    hackbools::bmenuOpen = false;
                }
            }
            if (GetAsyncKeyState(0x2D) & 1) {
                if (hackbools::bmenuOpen) {
                    hackbools::shouldopen = false;
                }
                else {
                    hackbools::shouldopen = true;
                }
            }

        

        //========================|RADAR HACK|================================
        if (hackbools::radarHack) { action::radarHack(); }

        //========================|bunny hop|================================
        if (hackbools::bhHack) { action::bunnyJump(); }

        //========================|flashbang|================================
        if (hackbools::flashbangHack) {
            localplayer::setflashbangAlpha(0);
        }
        if (!hackbools::flashbangHack) {
            localplayer::setflashbangAlpha(255);
        }
        //========================|triggerbot|================================
        if (hackbools::triggerbot::triggerbothack) { action::triggerBot(); }
        //========================|aimbot|================================
        if (hackbools::aimbot::aimbothack) { action::aimbotheader(); }
        if (!hackbools::aimbot::targetSight) { hackbools::aimbot::rage = true; }
    }
}