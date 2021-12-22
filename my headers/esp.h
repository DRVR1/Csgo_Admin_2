#pragma once
#include "worldtoscreen.h"
#include "dxdraw.h"

void espline(){
	if (get::EntityList() == false) { return; }
	if (get::LocalPlayerBase() == false) { return; }
	int localTeam = localplayer::teamcode();

	Vector3 bone;
	localplayer::setviewmatrix();

	float xi[64];
	float xf[64];
	float yi[64];
	float yf[64];

	for (int i = 1; i < 64; i++) {
		DWORD* entptr = entity::entptr(i);
		if (*entptr == 0x0 || NULL) { continue; }
		DWORD Entity = *entptr;
		bool Dormant = entity::isdormant(Entity); if (Dormant) { continue; }
		int EnmHealth = entity::health(Entity); if (EnmHealth < 1 || EnmHealth > 100) { continue; }
		bone = WorldToScreen(entity::getpos(1, Entity), entity::getpos(2, Entity), entity::getpos(3, Entity), globalData::localplayer::viewmatrix);
		//todo:: drawline with bone.pos
	}
}