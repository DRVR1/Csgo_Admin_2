#pragma once

int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN); int xhairx = SCREEN_WIDTH / 2;
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN); int xhairy = SCREEN_HEIGHT / 2;

struct Vector3 {
    float x, y, z;
};

struct Vector3 WorldToScreen(float posx, float posy, float posz, float viewmatrix[]) { //This turns 3D coordinates (ex: XYZ) int 2D coordinates (ex: XY).
    struct Vector3 out;
    float _x = viewmatrix[0] * posx + viewmatrix[1] * posy + viewmatrix[2] * posz + viewmatrix[3];
    float _y = viewmatrix[4] * posx + viewmatrix[5] * posy + viewmatrix[6] * posz + viewmatrix[7];
    out.z = viewmatrix[12] * posx + viewmatrix[13] * posy + viewmatrix[14] * posz + viewmatrix[15];

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