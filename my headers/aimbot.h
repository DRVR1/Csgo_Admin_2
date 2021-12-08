#pragma once
#include <Windows.h>
#include <stdio.h>
#include <math.h>

int closest = 0;
int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); int xhairx = SCREEN_WIDTH / 2;
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); int xhairy = SCREEN_HEIGHT / 2;

struct viewmatrix {
    float matrix[16];
}vm;

struct Vector3 {
    float x, y, z;
};

struct Vector3 WorldToScreen(float posx, float posy,float posz, struct viewmatrix matrix) { //This turns 3D coordinates (ex: XYZ) int 2D coordinates (ex: XY).
    struct Vector3 out;
    float _x = matrix.matrix[0] * posx + matrix.matrix[1] * posy + matrix.matrix[2] * posz + matrix.matrix[3];
    float _y = matrix.matrix[4] * posx + matrix.matrix[5] * posy + matrix.matrix[6] * posz + matrix.matrix[7];
    out.z = matrix.matrix[12] * posx + matrix.matrix[13] * posy + matrix.matrix[14] * posz + matrix.matrix[15];

    _x *= 1.f / out.z;
    _y *= 1.f / out.z;

    out.x = SCREEN_WIDTH * .5f;
    out.y = SCREEN_HEIGHT * .5f;

    out.x += 0.5f * _x * SCREEN_WIDTH + 0.5f;
    out.y -= 0.5f * _y * SCREEN_HEIGHT + 0.5f;

    return out;
}

float pythag(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
float distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
        pow(y2 - y1, 2) * 1.0);
}

int FindClosestEnemy(bool sight, bool aimteam) {
    if (get::EntityList() == false) { return 0; }
    if (get::LocalPlayerBase() == false) { return 0; }
    float Finish=0;
    float finish2=0;
    int ClosestEntity = 0;
    float Closest = FLT_MAX;
    float Closest2 = FLT_MAX;
    int localTeam = localplayer::teamcode();
    for (int i = 1; i < 64; i++) { 
        DWORD* entptr = entity::entptr(i);
        if (*entptr == 0x0 || NULL) { continue; }
        DWORD Entity = *entptr;
        if (!aimteam) {
            int EnmTeam = entity::team(Entity); if (EnmTeam == localTeam) continue;
        }
        int EnmHealth = entity::health(Entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
        int Dormant = entity::isdormant(Entity); if (Dormant) continue;
        float myposx = localplayer::getpos(1);
        float myposy = localplayer::getpos(2);
        float enemyx = entity::getpos(1, Entity);
        float enemyy = entity::getpos(2, Entity);
        if (sight) {
            Vector3 headBone = WorldToScreen(entity::gethead(1, Entity), entity::gethead(2, Entity), entity::gethead(3, Entity), vm);
            Finish = pythag(headBone.x, headBone.y, xhairx, xhairy);
            if (Finish < Closest) {
                Closest = Finish;
                ClosestEntity = i;
            }
        }
        else {
            finish2 = distance(enemyx, enemyy, myposx, myposy);
            if (finish2 < Closest2) {
                Closest2 = finish2;
                ClosestEntity = i;

            }
        }
    }

    return ClosestEntity;
}

//void FindClosestEnemythread() {
//    while (1) {
//        closest = FindClosestEnemy();
//        Sleep(1);
//    }
//}


void aimbot(bool sight, bool aimteam) {
        closest = FindClosestEnemy(sight, aimteam);

        if (closest == 0) { return; }
        if (get::EntityList() == false) { return; }
        if (get::LocalPlayerBase() == false) { return; }
        vm = *(viewmatrix*)(module::client + offset::ViewMatrix);
        DWORD* entptr = entity::entptr(closest);
        if (*entptr == 0x0 || NULL) { return; }
        DWORD currentEnt = *entptr;
        Vector3 closestw2shead = WorldToScreen(entity::gethead(1, currentEnt), entity::gethead(2, currentEnt), entity::gethead(3, currentEnt), vm);
        int health = entity::health(currentEnt);
        if (GetAsyncKeyState(VK_MENU)&& health>0) {
            if (closestw2shead.z >= 0.001f) {
                SetCursorPos(closestw2shead.x, closestw2shead.y);
            }
            else {
                get::ClientState();
                float xf = localplayer::getviewangle(1);
                xf += 180;
                xf = fmod(xf, 360); if (xf < 0) { xf += 360; }
                localplayer::setviewangle(xf, 0.18);
            }
            
        }
}
