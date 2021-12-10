#pragma once


namespace module {
	//===============|MODULES|=================================
	DWORD client = 0x0;
	DWORD engine = 0x0;
}

namespace offset {
	//===============|+MODULOS|=================================
	// + client.dll
	DWORD EntityList = 0x0; //not in hazedumper hexa x mio es 0x4DBF764 
	DWORD PlayerBase = 0x0; // dwLocalPlayer dword
	DWORD ForceJump = 0x0; //dwForceJump  byte 04||05
	DWORD ForceShoot = 0x0;
	DWORD ViewMatrix = 0x4DB30A4;
	

	// + engine.dll
	DWORD ClientState = 0x0; //dword dwClientState

	//===============|+BASES|=================================
	// + PlayerBase
	DWORD isGrounded = 0x0; //m_fFlags int 256||257 
	DWORD flashbangHex = 0x0; //not in hazedumper 255||0
	DWORD CrosshairId = 0x0;

	// + entitybase
	DWORD team = 0x0; //m_iTeamNum  (ct) 3|| (t) 2
	DWORD Health = 0x0;//m_iHealth  int
	DWORD isSpotted = 0x0; //m_bSpottedByMask binary mask 
	DWORD dormant = 0xED;
	DWORD positionX = 0x138;
	DWORD positionY = 0x13C;
	DWORD positionZ = 0x140;
	DWORD BoneMatrix = 0x26A8;

	namespace bone { //bodyparts
		int	Head = 8;
		int Neck = 7;
		int UpperBody = 6;
		int Body = 5;
		int LowerBody = 3;
		int Stomach = 4;
	}

	// + ClientState
	DWORD dwClientState_GetLocalPlayer = 0x0;
	DWORD ViewAngleY = 0x4D90;
	DWORD ViewAngleX = 0x4D94;

	//+isMenuOpenBase
	DWORD isMenuOpen = 0x0; //2 playing 4 pause 3 mainmenu
}

//===============|POINTERS|=================================
namespace pointer {
	//pointers
	DWORD entityListptr = 0x0;
	DWORD localPlayerptr = 0x0;
	DWORD clientStateptr = 0x0;
}
//===============|variables or static de-referenced|=================================
namespace base {
	DWORD isMenuOpenBase = 0x0;
	DWORD localPlayer = 0x0;
	DWORD entityList = 0x0;
	DWORD clientState = 0x0;
}

