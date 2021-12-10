#pragma once
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include "hackbools.h"

int closest = 0;
int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); int xhairx = SCREEN_WIDTH / 2;
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); int xhairy = SCREEN_HEIGHT / 2;

struct viewmatrix {
    float matrix[16];
}vm;

struct Vector3 {
    float x, y, z;
};

Vector3 headBone;

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

int FindClosestEnemy() {
    if (get::EntityList() == false) { return 0; }
    if (get::LocalPlayerBase() == false) { return 0; }
    int localTeam = localplayer::teamcode();
    int ClosestEntity = 0;

    float Closest = FLT_MAX;
    float Finish = 0;

    float finish2 = 0;
    float Closest2 = FLT_MAX;
    for (int i = 1; i < 64; i++) { 
        DWORD* entptr = entity::entptr(i);
        if (*entptr == 0x0 || NULL) { continue; }
        DWORD Entity = *entptr;
        if (!hackbools::aimbot::targetTeam) {
            int EnmTeam = entity::team(Entity); if (EnmTeam == localTeam) continue;
        }
        int EnmHealth = entity::health(Entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
        int Dormant = entity::isdormant(Entity); if (Dormant) continue;

        if (hackbools::aimbot::targetSight) { //set closest by distance from center of the screen to target
            Vector3 Bone = WorldToScreen(entity::getbodypart(1, hackbools::aimbot::bodypart, Entity), entity::getbodypart(2, hackbools::aimbot::bodypart, Entity), entity::getbodypart(3, hackbools::aimbot::bodypart, Entity), vm);
            Finish = pythag(Bone.x, Bone.y, xhairx, xhairy);
            if (Finish < Closest) {
                 Closest = Finish;
                 ClosestEntity = i; 
            }
        }
        if(!hackbools::aimbot::targetSight) { //set closest by distance to player
            float myposx = localplayer::getpos(1);
            float myposy = localplayer::getpos(2);
            float myposz = localplayer::getpos(3);
            float enemyx = entity::getpos(1, Entity);
            float enemyy = entity::getpos(2, Entity);
            float enemyz = entity::getpos(3, Entity);
            finish2 = pythag(enemyx, enemyy, myposx, myposy);
            if (finish2 < Closest2) {
                Closest2 = finish2;
                ClosestEntity = i;
            }
        }
    }
    return ClosestEntity;
}



void aimbot() {
        closest = FindClosestEnemy();

        if (get::EntityList() == false) { return; }
        if (get::LocalPlayerBase() == false) { return; }

        
        if (closest == 0) { return; }

        vm = *(viewmatrix*)(module::client + offset::ViewMatrix); //todo: poner en gets
        DWORD* entptr = entity::entptr(closest);
        if (*entptr == 0x0 || NULL) { return; }
        DWORD currentEnt = *entptr;
        Vector3 closestw2shead = WorldToScreen(entity::getbodypart(1, hackbools::aimbot::bodypart , currentEnt), entity::getbodypart(2, hackbools::aimbot::bodypart, currentEnt), entity::getbodypart(3, hackbools::aimbot::bodypart, currentEnt), vm);
        float rdistance = pythag(closestw2shead.x, closestw2shead.y, xhairx, xhairy);
        if (GetAsyncKeyState(VK_MENU)&0x8000) {
            if (closestw2shead.z >= 0.001f ) {
                if (rdistance < hackbools::aimbot::fov || hackbools::aimbot::rage) {
                    if (hackbools::aimbot::yawonly) {
                        POINT cursor;
                        GetCursorPos(&cursor);
                        SetCursorPos(closestw2shead.x, cursor.y);
                    }
                    else {
                        SetCursorPos(closestw2shead.x, closestw2shead.y);
                    }
                }
            }else {
                if (hackbools::aimbot::rage) {
                    get::ClientState();
                    float xf = localplayer::getviewangle(1);
                    xf += 180;
                    xf = fmod(xf, 360); if (xf < 0) { xf += 360; }
                    localplayer::setviewangle(xf, 0.18);
                }
            }

            
        }
}
