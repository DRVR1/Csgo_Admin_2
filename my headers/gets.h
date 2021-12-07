#include "Offsets.h"

namespace get {
	bool EntityList() { //por ahora no necesita desreferenciar
		//if (*(DWORD*)pointer::entityListptr == NULL || 0x0) { return false; }
		base::entityList = (DWORD)pointer::entityListptr;
		return  true;
	}
	bool LocalPlayerBase() {
		if (*(DWORD*)pointer::localPlayerptr == NULL || 0x0) { return false; }
		base::localPlayer = *(DWORD*)pointer::localPlayerptr; 
		return true; 
	}
	bool ClientState() {
		if (*(DWORD*)pointer::localPlayerptr == NULL || 0x0) { return false; }
		base::clientState = *(DWORD*)(pointer::clientStateptr);
		return true;
	}
}
namespace localplayer {
	int teamcode() {
		return *(int*)(base::clientState + offset::dwClientState_GetLocalPlayer);
	}
	
	int onsight() {
		return *(int*)(base::localPlayer + offset::CrosshairId);
	}

	bool isgrounded() {
		if (*(int*)(base::localPlayer + offset::isGrounded) == 257) { 
			return true;
		}
		else {
			return false;
		}
	}

	void forcejump() {
		*(int*)(module::client + offset::ForceJump) = 5;
	}
	void forcenotjump() {
		*(int*)(module::client + offset::ForceJump) = 4;
	}
}
namespace entity {
	DWORD* entptr(int iterator) {
		DWORD* output = (DWORD*)((DWORD)base::entityList + (iterator * 0x10));
		return output;
	}
	bool isdormant(DWORD currentEnt) {
		bool output = *(bool*)(currentEnt + offset::dormant);
		return output;
	}
	float getpos(int wich, DWORD currentEnt) {
		float x, y, z;
		switch (wich){
			case 1:
				 x = *(float*)(currentEnt + offset::positionX);
				return x;
				break;
			case 2:
				 y = *(float*)(currentEnt + offset::positionY);
				return y;
				break;
			case 3:
				 z = *(float*)(currentEnt + offset::positionZ);
				return z;
				break;
		}
	
	}
}
