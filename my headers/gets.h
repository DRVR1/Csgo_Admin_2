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

