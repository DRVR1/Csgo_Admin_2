#pragma once
#include "Offsets.h"
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <conio.h>
#include <stdio.h>

int wait;
namespace gamefunc {

    void acceptmatch() {
        void(*acceptmatch)() = (void(*)())(offset::function::autoAccept);
        wait++;
        if (wait == 2000) { acceptmatch(); wait = 0; }
    }
}
