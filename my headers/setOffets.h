#pragma once
#include "Offsets.h"
#include "signature.h"

#include "readOffsetAddress.h"

DWORD errorCode = 0x1;
char clientmodule[] = "client.dll";
char enginemodule[] = "engine.dll";


DWORD sub = 0x2000; //subs from offset to make a bigger search zone

bool stablishOffsets() {

	if (hackbools::csgoUpdated) {
		removeFile();
	}
	else { readOffsets(); }

	// + client.dll
	offset::EntityList = findpattern(true, true, (0x402C2D - sub), offsetload::offset[0], 2, 0x10, clientmodule, "\x8B\x88\x00\x00\x00\x00\x85\xC9\x74\x42\x8B\x01\xFF\x50\x00\x8B\xF8\x85\xFF\x74\x37\x8B\x17\x8B\xCF\x8B\x92\x00\x00\x00\x00\xFF\xD2\x84\xC0\x74\x27", "xx????xxxxxxxx?xxxxxxxxxxxx????xxxxxx");
	if (offset::EntityList == errorCode) { return false; }

	offset::PlayerBase = findpattern(true, true, (0x2AC7A9 - sub), offsetload::offset[1], 3, 4, clientmodule, "\x8D\x34\x85\x00\x00\x00\x00\x89\x15\x00\x00\x00\x00\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", "xxx????xx????xxxxxxxxx");
	if (offset::PlayerBase == errorCode) { return false; }

	offset::ForceJump = findpattern(true, true, (0x2ED64D - sub), offsetload::offset[2], 2, 0, clientmodule, "\x89\x0D\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x8B\xF2\x8B\xC1\x83\xCE\x08\x24\x03\x8B\xC7\x0F\x44\xF2", "xx????xx????xxxxxxxxxxxxxx");
	if (offset::ForceJump == errorCode) { return false; }

	offset::ForceShoot = findpattern(true, true, (0x2ED585 - sub), offsetload::offset[3], 2, 0, clientmodule, "\x8B\x0D\x00\x00\x00\x00\x8B\xD6\x8B\xC1\x83\xCA\x01\x24\x03", "xx????xxxxxxxxx");
	if (offset::ForceShoot == errorCode) { return false; }

	base::isMenuOpenBase = findpattern(false, true, (0x47B3F8 - sub), offsetload::offset[4], 1, 0, clientmodule, "\xA1\x00\x00\x00\x00\x32\xD2\xB9\x00\x00\x00\x00\x89\x55\xF8\x8B\x40\x74\xFF\xD0", "x????xxx????xxxxxxxx");
	if (base::isMenuOpenBase == errorCode) { return false; }

	// + engine.dll
	offset::ClientState = findpattern(true, true, (0xB6E7B - sub), offsetload::offset[5], 1, 0, enginemodule, "\xA1\x00\x00\x00\x00\x33\xD2\x6A\x00\x6A\x00\x33\xC9\x89\xB0", "x????xxxxxxxxxx");
	if (offset::ClientState == errorCode) { return false; }

	// + PlayerBase
	offset::isGrounded = findpattern(false, true, (0x3DEA8B - sub), offsetload::offset[6], 2, 0, clientmodule, "\xF6\x80\x04\x01\x00\x00\x02\x75\x6F\x84\xD2\x74\x70\x8B\x87\x00\x00\x00\x00\x05\x00\x00\x00\x00\xF3\x0F\x10\x10", "xxxxxxxxxxxxxxx????x????xxxx");
	if (offset::isGrounded == errorCode) { return false; }

	offset::flashbangHex = findpattern(false, true, (0x3AC4A3 - sub), offsetload::offset[7], 4, 0, clientmodule, "\xF3\x0F\x10\x9E\x00\x00\x00\x00\x0F\x2F\xD3\x0F\x83\x00\x00\x00\x00\x80\xBE\x68\x04\x01\x00\x00\x0F\x28\xC1\xF3\x0F\x10\xB6\x00\x00\x00\x00\x0F\x28\xE5", "xxxx????xxxxx????xxxxxxxxxxxxxx????xxx");
	if (offset::flashbangHex == errorCode) { return false; }

	offset::CrosshairId = findpattern(false, true, (0x3BD0D3 - sub), offsetload::offset[8], 2, 0, clientmodule, "\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00\x8B\x0D\x00\x00\x00\x00\x81\xF9\x00\x00\x00\x00\x75\x0C\xA1\x00\x00\x00\x00\x35\x00\x00\x00\x00\xEB\x07\x8B\x01\x8B\x40\x34\xFF\xD0\x83\xF8\x02\x0F\x84\x00\x00\x00\x00\x8D\x45\xC7\xB9\x00\x00\x00\x00", "xx????????xx????xx????xxx????x????xxxxxxxxxxxxxx????xxxx????");
	if (offset::CrosshairId == errorCode) { return false; }

	// + entitybase
	offset::team = findpattern(false, true, (0x1E3990 - sub), offsetload::offset[9], 2, 0, clientmodule, "\x8B\x81\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x8B\x81\x00\x00\x00\x00\xC3\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x8B\x01\xFF\xA0\x00\x00\x00\x00\xCC\xCC\xCC\xCC\xCC\xCC\xCC\xCC\x55\x8B\xEC\x57\x8B\xF9\x8B\x4D\x08\x85\xC9\x75\x07\x32\xC0\x5F\x5D\xC2\x04\x00\x8B\x01\x56\xFF\x90\x00\x00\x00\x00\x8B\x17\x8B\xCF", "xx????xxxxxxxxxxxx????xxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx");
	if (offset::team == errorCode) { return false; }

	offset::Health = findpattern(false, true, (0x3DED5C - sub), offsetload::offset[10], 2, 0, clientmodule, "\x83\xB9\x00\x01\x00\x00\x00\x0F\x8E\x00\x00\x00\x00\x8B\x57\x08\xF3\x0F\x10\x5A\x5C\xF3\x0F\x11\x5C\x24\x38\xF3\x0F\x10\x42\x60\xF3\x0F\x11\x44\x24\x3C\xF3\x0F\x10\x52\x64", "xxxxxxxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	if (offset::Health == errorCode) { return false; }

	offset::isSpotted = findpattern(false, true, (0x1aab3f - sub), offsetload::offset[11], 3, 0, clientmodule, "\x85\x94\x81\x00\x00\x00\x00\x0F\x95\xC0\x84\xC0\x75\x21\x8B\x7D\x08\x83\xC7\x10", "xxx????xxxxxxxxxxxxx");
	if (offset::isSpotted == errorCode) { return false; }


	// + ClientState
	offset::dwClientState_GetLocalPlayer = findpattern(false, true, (0xE000B - sub), offsetload::offset[12], 2, 0, enginemodule, "\x8B\x80\x00\x00\x00\x00\x40\x5D\xC2\x04\x00\x83\xC8\xFF\x5D", "xx????xxxxxxxxx");
	if (offset::dwClientState_GetLocalPlayer == errorCode) { return false; }

	//+isMenuOpenBase
	offset::isMenuOpen = findpattern(false, true, (0x4326d0 - sub), offsetload::offset[13], 2, 0, clientmodule, "\x8B\x81\x00\x00\x00\x00\x83\xC0\xFD\x83\xF8\x01\x0F\x96\xC0\xC3", "xx????xxxxxxxxxx");
	if (offset::isMenuOpen == errorCode) { return false; }

	// + client.dll
	offset::function::autoAccept = findpattern(false, false, (0x5CDE60 - sub), offsetload::offset[14], 0, 0, clientmodule, "\x55\x8B\xEC\x83\xE4\xF8\x8B\x4D\x08\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x85\xC0\x75\x12", "xxxxxxxxxx????x????xxxx");
	if (offset::function::autoAccept == errorCode) { return false; }

	//===================|setting things that require the offsets|====================
	module::client = (DWORD)GetModuleHandle(clientmodule);
	module::engine = (DWORD)GetModuleHandle(enginemodule);
	pointer::entityListptr = (DWORD)(module::client + offset::EntityList);
	pointer::localPlayerptr = (DWORD)(module::client + offset::PlayerBase);
	pointer::clientStateptr = (DWORD)(module::engine + offset::ClientState);

	return true;
}
