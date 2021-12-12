//USE MULTIBYTE CHARACTER SET 
#pragma once 
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <stdio.h>

#include <conio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

    bool debugMode = false;

	

	//------how to use moduleinfo-----
	//MODULEINFO mInfo = GetModuleInfo(module); 
	//DWORD base = (DWORD)mInfo.lpBaseOfDll;
	//DWORD size = (DWORD)mInfo.SizeOfImage;
	MODULEINFO GetModuleInfo(char* module) {
	MODULEINFO modInfo = { 0 };
	HMODULE hModule = GetModuleHandle(module);
	if (hModule == 0) { return modInfo; }
	GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
	return modInfo;
	}

	void removeFile() {
			remove("performance.log");
			DeleteFileA("performance.log");
	}

	std::ofstream logs;
	
	
	//EXAMPLE:
	//relative means the offsets comes from adding the module + the offset
	//dereference and sum makes the output to be not the raw address but what is contained inside, and sum is just in case the result need to change in a small amount
	//padding is used when dereferencing. to select wich 4 bytes we take from the dereferenced module+address given
	//add (sum) is the value we add when we got those 4 bytes, its just for some cases
	//startpos is module+startpos, used for faster search. if you cant find address decrease startpos
	//return should be an offset from the module, to a pointer that points playerbase for example, if dereferenceandsum is false, return should be an address
	DWORD findpattern(BOOL relative,BOOL dereferenceandsum, DWORD startpos,DWORD readFromStartpos, DWORD padding, DWORD add, char* module, const char* pattern, const char* mask) {
		
		MODULEINFO mInfo = GetModuleInfo(module);
		DWORD modulebase = (DWORD)mInfo.lpBaseOfDll;
		DWORD modulesize = (DWORD)mInfo.SizeOfImage;

		DWORD patternLenght = (DWORD)strlen(mask);

		bool found = false;
		DWORD final = 0x0;
		DWORD errorCode = 0x1;

		if (!hackbools::csgoUpdated) { startpos = readFromStartpos; }

		for (DWORD i = startpos; i < modulesize; i++) {
			printf("scanning pattern in 0x%x PRESS 9 TO CANCEL\n", (modulebase + i));

			if (GetAsyncKeyState(0x39) & 1) {
				printf("cancelling operation...\n");
				return errorCode;
			}

			for (DWORD j = 0; j < patternLenght; j++) {
				if (*(char*)(modulebase + i) != pattern[0]) { j = 0; break; }

				if (*(char*)(modulebase + i + j) == pattern[j] || mask[j] == '?') {
					final = modulebase + i;
					found = true;
				}
				else { found = false; break; }
			}
			if (found) {
				printf("offset address is 0x%x (%s + 0x%x)\n", final, module, (final - modulebase));
				DWORD rel = (final - modulebase);

				if (hackbools::csgoUpdated) {
					if (offsetload::placeoutput) {
						logs.open("performance.log");
						offsetload::placeoutput = false;
					}
					logs << rel << std::endl;
				}

				if (dereferenceandsum) {
					DWORD insider = (*(DWORD*)(final + padding)); //takes 4 bytes contained in the selected address
					printf("it has inside: 0x%x\n", insider);
				    insider += add; //just adding a number w/o dereferencing
					printf("adding offset %d result is: 0x%x\n",add, insider);
					if (relative) {
						insider = insider - modulebase; //removing modulebase to make it an offset not a raw address
					}
					printf("returning 0x%x\n", insider);
					if (debugMode) { printf("mask: %s\n", mask); system("pause"); }
					return insider;
				}
				else { //return raw address
					return (final - modulebase);
				}


			}
		}
		if (!found) {
			printf("%s not found\n",mask); return errorCode;
		}



	}


	