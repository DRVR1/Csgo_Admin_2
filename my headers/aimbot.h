#pragma once
#include <Windows.h>
#include <stdio.h>

struct vector3position {
    float x, y, z;
};

int width = GetSystemMetrics(SM_CXSCREEN); int centerx = width / 2;
int height = GetSystemMetrics(SM_CYSCREEN); int centery = height / 2;

void aimbot() {
        get::EntityList();

        for (int i = 1; i < 64; i++) {
            DWORD* entptr = entity::entptr(i);
            if (*entptr == 0x0 || NULL) { continue; }
            DWORD currentEnt = *entptr;
            bool dormant = entity::isdormant(currentEnt);
            if (dormant) {
                printf("entity %d is dormant\n", i);
            }
            if (!dormant) {
                printf("entity %d NOT dormant\n", i);
            }
            vector3position wiggum;
            

        }
        system("cls");

}