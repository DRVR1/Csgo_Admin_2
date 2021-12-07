#pragma once
#include "Offsets.h"
#include <bitset>
#include "gets.h"


namespace action {


    void radarHack() {
        get::EntityList(); 
        get::LocalPlayerBase();
        if (get::ClientState() == false) { return; }

        for (int i = 1; i < 64; i++) {
            DWORD* entptr = entity::entptr(i);
            if (*entptr == 0x0 || NULL) { continue; }
            DWORD currentEnt = *entptr;
            std::bitset<32> x = *(int*)(currentEnt + offset::isSpotted);
            x[localplayer::teamcode()] = 1; //va desde derecha a izquierda en la mascara la cantidad de veces que el teamcode indique, ese bit se pone en 1
            *(int*)(currentEnt + offset::isSpotted) = (int)(x.to_ulong());
        }
    }

    void bunnyJump() {
        if (get::LocalPlayerBase() == false) { return; }

        if (localplayer::isgrounded()) {
            if (GetAsyncKeyState(0x20) & 0x8000) {
                localplayer::forcejump();
            }
            else {
                localplayer::forcenotjump();
            }
        }
        else {
            localplayer::forcenotjump();
        }
    }
    void triggerBot() {
        DWORD team = 0x0;
        DWORD myteam = 0x0;

        if (get::LocalPlayerBase() == false) {  return; }

        if (get::EntityList() == false) { return; }

        DWORD onsight = localplayer::onsight();
        

        if (onsight <= 64 && onsight > 1) {}  else { return; }
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



