#pragma once
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>


#include <stdio.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <conio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

struct Vec2 {
	float X, Y;
};
struct Vec3 {
	float X, Y, Z;
};
struct espcolor {
	float R, G, B, A;

};

void ConvertToRange(Vec2& Point)
{
	Point.X /= 1920.0f;
	Point.X *= 2.0f;
	Point.X -= 1.0f;

	Point.Y /= 1080.0f;
	Point.Y *= 2.0f;
	Point.Y -= 1.0f;
}


bool WorldToScreen(const Vec3& VecOrigin, Vec2& VecScreen, float* Matrix)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection Matrix = clipCoords
	VecScreen.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
	VecScreen.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
	float W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];

	if (W < 0.01f)
		return false;

	//perspective division, dividing by clip.W = NormaliZed Device Coordinates
	Vec2 NDC;
	NDC.X = VecScreen.X / W;
	NDC.Y = VecScreen.Y / W;

	VecScreen.X = (1920 / 2 * NDC.X) + (NDC.X + 1920 / 2);
	VecScreen.Y = (1080 / 2 * NDC.Y) + (NDC.Y + 1080 / 2);

	ConvertToRange(VecScreen);

	return true;
}

/*void DrawLine(Vec2& Start, Vec2& End, struct espcolor* Color)
{
	glBegin(GL_LINES);
	glColor4f(Color->R, Color->G, Color->B, Color->A);
	glVertex2f(Start.X, Start.Y);
	glVertex2f(End.X, End.Y);
	glEnd();
}*/
void DrawLine()
{
	glBegin(GL_LINES);
	glColor4f(255,255,255,255);
	glVertex2f(0, 0);
	glVertex2f(1000, 1000);
	glEnd();
}