#pragma once
#include <stdio.h>
#include <windows.h>
#include <tlHelp32.h>
#include <vector>
#include <iostream>

//get PID from window name (input)  ejemplo: DWORD caca = getPID("AssaultCube");
DWORD getPID(const char input[]) {

	DWORD procID = 0;
	HWND window = FindWindowA(NULL, input); //window name here

	if (window != NULL) {
		GetWindowThreadProcessId(window, &procID);
	}
	else {
		printf("Window not found wtf!!\n");
		system("pause");
		exit(0);
	}

	return procID;


}

//get get PID 2  	DWORD pid = getPID2(L"ac_client.exe");

DWORD getPID2(const wchar_t input[]) {
	DWORD procID = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (snapshot != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 procEntry;
		procEntry.dwSize = sizeof(procEntry);
		if (Process32First(snapshot, &procEntry)) {
			do {
				if (!_wcsicmp(procEntry.szExeFile, input)) //program name here
				{
					procID = procEntry.th32ProcessID;
					break;
				}
			} while (Process32Next(snapshot, &procEntry));

		}
	}
	CloseHandle(snapshot);
	return procID;

}

//get module base 	uintptr_t modulebase = getmodulebase(L"ac_client.exe", procID);
uintptr_t getmodulebase(const wchar_t* input, DWORD procID) {
	uintptr_t modulebase = 0x0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!_wcsicmp(modEntry.szModule, input)) //program name here
				{
				    modulebase = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));

		}
	}
	return modulebase;
}

//read int
int readint(DWORD procID,HANDLE handler, uintptr_t modulebase, std::vector<unsigned int>offsets) {
	int output = 0; 
	modulebase = modulebase + offsets[0];
	uintptr_t currentadress = modulebase;
	for (int i = 0; i < offsets.size()-1; i++) {
		ReadProcessMemory(handler, (BYTE*)currentadress, &currentadress, sizeof(currentadress), NULL);
		currentadress = currentadress + offsets[i+1];
	}
	ReadProcessMemory(handler, (BYTE*)currentadress, &output, sizeof(output), NULL);
	return output;
}
//write int
void writeint(DWORD procID, HANDLE handler, uintptr_t modulebase, std::vector<unsigned int>offsets, int newvalue) {
	modulebase = modulebase + offsets[0];
	uintptr_t currentadress = modulebase;
	for (int i = 0; i < offsets.size() - 1; i++) {
		ReadProcessMemory(handler, (BYTE*)currentadress, &currentadress, sizeof(currentadress), NULL);
		currentadress = currentadress + offsets[i + 1];
	}
	WriteProcessMemory(handler, (BYTE*)currentadress, &newvalue, sizeof(newvalue), NULL);
}

float readfloat(DWORD procID, HANDLE handler, uintptr_t modulebase, std::vector<unsigned int>offsets) {
	float output = 0;
	modulebase = modulebase + offsets[0];
	uintptr_t currentadress = modulebase;
	for (int i = 0; i < offsets.size() - 1; i++) {
		ReadProcessMemory(handler, (BYTE*)currentadress, &currentadress, sizeof(currentadress), NULL);
		currentadress = currentadress + offsets[i + 1];
	}
	ReadProcessMemory(handler, (BYTE*)currentadress, &output, sizeof(output), NULL);
	return output;
}
//write float
void writefloat(DWORD procID, HANDLE handler, uintptr_t modulebase, std::vector<unsigned int>offsets, float newvalue) {
	modulebase = modulebase + offsets[0];
	uintptr_t currentadress = modulebase;
	for (int i = 0; i < offsets.size() - 1; i++) {
		ReadProcessMemory(handler, (BYTE*)currentadress, &currentadress, sizeof(currentadress), NULL);
		currentadress = currentadress + offsets[i + 1];
	}
	WriteProcessMemory(handler, (BYTE*)currentadress, &newvalue, sizeof(newvalue), NULL);
}


//cambia el codigo assembly del programa. dst = address destino, src = fuente, osea que funcion insertamos, ej dec, inc
//size es la cantidad de bytes que cambiamos, si la fuente es un byte solo y ponemos size 2, el segundo byte va a ser un 00.
void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE handler) {
	DWORD oldprotect;
	VirtualProtectEx(handler, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(handler, dst, src, size, nullptr);
	VirtualProtectEx(handler, dst, size, oldprotect, &oldprotect);
}



void NopEx(BYTE * addr, unsigned int size, HANDLE handler) {
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	PatchEx(addr, nopArray, size, handler);
	delete[] nopArray;
}




std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

// DWORD ApplicationPID = GetProcessId(GetCurrentProcess());
// DWORD User32Size = GetModuleSize(ApplicationPID, "User32.dll");
DWORD GetModuleSize(DWORD processID, char* module)
{
 
    HANDLE hSnap;
    MODULEENTRY32 xModule;
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
    xModule.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnap, &xModule)) {
        while (Module32Next(hSnap, &xModule)) {
            if (!strncmp((char*)xModule.szModule, module, 8)) {
                CloseHandle(hSnap);
                return (DWORD)xModule.modBaseSize;
            }
        }
    }
    CloseHandle(hSnap);
    return 0;
}



