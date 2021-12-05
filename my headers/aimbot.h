#pragma once
#include <Windows.h>
#include <stdio.h>

class Vector3 {
public:
    float x, y, z;
    Vector3() : x(0.f), y(0.f), z(0.f) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

int width = GetSystemMetrics(SM_CXSCREEN); int centerx = width / 2;
int height = GetSystemMetrics(SM_CYSCREEN); int centery = height / 2;

void aimbot() {
 


}