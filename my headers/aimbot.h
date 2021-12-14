#pragma once
#include "hackbools.h"


int closest = 0;
int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); int xhairx = SCREEN_WIDTH / 2;
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); int xhairy = SCREEN_HEIGHT / 2;

namespace viewmatrix {
    struct viewmatrix {
        float matrix[16];
    }vm;
}


struct Vector3 {
    float x, y, z;
};

Vector3 headBone;

struct Vector3 WorldToScreen(float posx, float posy,float posz, struct viewmatrix::viewmatrix matrix) { //This turns 3D coordinates (ex: XYZ) int 2D coordinates (ex: XY).
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
        int Dormant = entity::isdormant(Entity); if (Dormant) continue;
        int EnmHealth = entity::health(Entity); if (EnmHealth < 1 || EnmHealth > 100) continue;
        if (!hackbools::aimbot::targetTeam) {
            int EnmTeam = entity::team(Entity); if (EnmTeam == localTeam) continue;
        }
            Vector3 Bone = WorldToScreen(entity::getbodypart(1, hackbools::aimbot::bodypart, Entity), entity::getbodypart(2, hackbools::aimbot::bodypart, Entity), entity::getbodypart(3, hackbools::aimbot::bodypart, Entity), viewmatrix::vm);
            Finish = pythag(Bone.x, Bone.y, xhairx, xhairy);
            if (Finish < Closest) {
                 Closest = Finish;
                 ClosestEntity = i; 
            }

    }
    return ClosestEntity;
}

void aimbot() {
        closest = FindClosestEnemy();

        if (get::EntityList() == false) { return; }
        if (get::LocalPlayerBase() == false) { return; }

        
        if (closest == 0) { hackbools::aimbot::oscillation::canDraw = false;  return; }

        viewmatrix::vm = *(viewmatrix::viewmatrix*)(module::client + offset::ViewMatrix); //todo: poner en gets
        DWORD* entptr = entity::entptr(closest);
        if (*entptr == 0x0 || NULL) { return; }
        DWORD currentEnt = *entptr;
        Vector3 targetPos = WorldToScreen(entity::getbodypart(1, hackbools::aimbot::bodypart , currentEnt), entity::getbodypart(2, hackbools::aimbot::bodypart, currentEnt), entity::getbodypart(3, hackbools::aimbot::bodypart, currentEnt), viewmatrix::vm);
        float rdistance = pythag(targetPos.x, targetPos.y, xhairx, xhairy);

        //if (!hackbools::aimbot::aimtrhoughwall) {
        //    if (!entity::isbSpotted(currentEnt)) { return; }
        //}

        //============|DEBUG|===========
        POINT cursor;
        GetCursorPos(&cursor);
        hackbools::aimbot::debug::gotoX = targetPos.x;
        hackbools::aimbot::debug::gotoY = targetPos.y;
        hackbools::aimbot::debug::gotoZ = targetPos.z;
        hackbools::aimbot::debug::mouseposX = cursor.x;
        hackbools::aimbot::debug::mouseposY = cursor.y;
        //============|DEBUG ENDS|=======
        if (targetPos.z >= 0.001f) { hackbools::aimbot::oscillation::canDraw = true; }
        else {
            hackbools::aimbot::oscillation::canDraw = false;
        }
        if (GetAsyncKeyState(hackbools::aimbot::toggleKey)&0x8000) {
            if (targetPos.z >= 0.001f ) {
                if (rdistance < hackbools::aimbot::fov || !hackbools::aimbot::bfov) {
                        //SetCursorPos(targetPos.x, cursor.y);
                        POINT cursor;
                        if (hackbools::aimbot::speed != 0) { //todo: smooth in-range to avoid tilting
                            GetCursorPos(&cursor);
                            if (targetPos.x < cursor.x && (xhairx - hackbools::aimbot::oscillation::antiOscillator) > targetPos.x) {
                                SetCursorPos(cursor.x - hackbools::aimbot::speed, cursor.y);
                            }
                            if (targetPos.x > cursor.x && (xhairx + hackbools::aimbot::oscillation::antiOscillator) < targetPos.x) {
                                SetCursorPos(cursor.x + hackbools::aimbot::speed, cursor.y);
                            }
                            GetCursorPos(&cursor);
                            if (!hackbools::aimbot::yawonly) {
                                if (targetPos.y > cursor.y && (xhairy + hackbools::aimbot::oscillation::antiOscillator) < targetPos.y) {
                                    SetCursorPos(cursor.x, cursor.y + hackbools::aimbot::speed);
                                }
                                if (targetPos.y < cursor.y && (xhairy - hackbools::aimbot::oscillation::antiOscillator) > targetPos.y) {
                                    SetCursorPos(cursor.x, cursor.y - hackbools::aimbot::speed);
                                }
                            }

                            Sleep(hackbools::aimbot::sleepTime);
                        }
                        else {
                            
                            if (hackbools::aimbot::yawonly) {
                                GetCursorPos(&cursor);
                                SetCursorPos(targetPos.x, cursor.y);
                            }
                            else {
                                SetCursorPos(targetPos.x, targetPos.y);
                            }
                        }
                }
            } else {
                if (!hackbools::aimbot::bfov) {
                    get::ClientState();
                    float xf = localplayer::getviewangle(1);
                    xf += 180;
                    xf = fmod(xf, 360); if (xf < 0) { xf += 360; }
                    localplayer::setviewangle(xf, 0.18);
                }
            }

            
        }
}
