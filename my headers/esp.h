#pragma once
#include "worldtoscreen.h"
#include "dxdraw.h"

void espline(){
	if (get::EntityList() == false) { return; }
	if (get::LocalPlayerBase() == false) { return; }
	int localTeam = localplayer::teamcode();

	Vector3 bone;
	localplayer::setviewmatrix();

	ImVec4 teamcolor;
	teamcolor.x = hackbools::visuals::esp::esplinecolorteam[0];
	teamcolor.y = hackbools::visuals::esp::esplinecolorteam[1];
	teamcolor.z = hackbools::visuals::esp::esplinecolorteam[2];
	teamcolor.w = hackbools::visuals::esp::esplinecolorteam[3];
	ImU32 teamcolor2 = ImGui::ColorConvertFloat4ToU32(teamcolor);

	ImVec4 enemycolor;
	enemycolor.x = hackbools::visuals::esp::esplinecolorenemy[0];
	enemycolor.y = hackbools::visuals::esp::esplinecolorenemy[1];
	enemycolor.z = hackbools::visuals::esp::esplinecolorenemy[2];
	enemycolor.w = hackbools::visuals::esp::esplinecolorenemy[3];
	ImU32 enemycolor2 = ImGui::ColorConvertFloat4ToU32(enemycolor);

	for (int i = 1; i < 64; i++) {
		DWORD* entptr = entity::entptr(i);
		if (*entptr == 0x0 || NULL) { continue; }
		DWORD Entity = *entptr;
		bool Dormant = entity::isdormant(Entity); if (Dormant) { continue; }
		int EnmHealth = entity::health(Entity); if (EnmHealth < 1 || EnmHealth > 100) { continue; }
		bone = WorldToScreen(entity::getpos(1, Entity), entity::getpos(2, Entity), entity::getpos(3, Entity), globalData::localplayer::viewmatrix);
		if (bone.z < 0.01) { continue; }

		if (entity::team(Entity) == localTeam) {
			drawline(xhairx, SCREEN_HEIGHT, bone.x, bone.y, hackbools::visuals::esp::tickness, teamcolor2);
		}
		else {
			drawline(xhairx, SCREEN_HEIGHT, bone.x, bone.y, hackbools::visuals::esp::tickness, enemycolor2);
		}
		
	}
}