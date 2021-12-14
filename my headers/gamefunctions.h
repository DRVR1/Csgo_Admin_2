#pragma once
#include "Offsets.h"
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <conio.h>
#include <stdio.h>


namespace gamefunc {

    void acceptmatch() {
        void(*acceptmatch)() = (void(*)())(offset::function::autoAccept);
        acceptmatch();
    }
}
