#pragma once
#include "Offsets.h"
#include <bitset>


namespace action {


    void radarHack() {
        base::entityList = (DWORD)pointer::entityListptr;

        for (int i = 1; i < 64; i++) {
            DWORD* entptr = (DWORD*)((DWORD)base::entityList + (i * 0x10));
            if (*entptr == 0x0 || NULL) { continue; }
            DWORD currentEnt = *entptr;

            std::bitset<32> x = *(int*)(currentEnt + offset::isSpotted);
            x[*(int*)(base::clientState + offset::dwClientState_GetLocalPlayer)] = 1; //position must be playercode
            *(int*)(currentEnt + offset::isSpotted) = (int)(x.to_ulong());
        }
    }

    void bunnyJump() {
        if (*(DWORD*)pointer::localPlayerptr == NULL || 0x0) { return; }
        else { base::localPlayer = *(DWORD*)pointer::localPlayerptr; }

        if (*(int*)(base::localPlayer + offset::isGrounded) == 257) {
            if (GetAsyncKeyState(0x20) & 0x8000) {
                *(int*)(module::client+ offset::ForceJump) = 5;
            }
            else {
                *(int*)(module::client + offset::ForceJump) = 4;
            }
        }
        else {
            *(int*)(module::client + offset::ForceJump) = 4;
        }
    }

    void triggerBot() {
        DWORD team = 0x0;
        DWORD myteam = 0x0;
        if (*(DWORD*)pointer::localPlayerptr == NULL || 0x0) { return; }
        base::localPlayer = *(DWORD*)(module::client + offset::PlayerBase);
        base::entityList = (DWORD)pointer::entityListptr;
        DWORD onsight = *(int*)(base::localPlayer + offset::CrosshairId);
       
            if (onsight <= 64 && onsight > 1) {}
            else { return; }
            DWORD* entptr = (DWORD*)(base::entityList + (0x10 * (onsight - 0x1)));
            DWORD currentEnt = *entptr;
            if (*(DWORD*)(currentEnt + offset::team) == 0x0 || NULL) { return; }
            team = *(DWORD*)(currentEnt + offset::team);
            myteam = *(DWORD*)(base::localPlayer + offset::team);
            if (GetAsyncKeyState(0x12) & 0x8000) {
                if (team != myteam) {
                    *(int*)(module::client + offset::ForceShoot) = 5;
                    Sleep(10);
                    *(int*)(module::client + offset::ForceShoot) = 4;
                }
            }
    }



}



