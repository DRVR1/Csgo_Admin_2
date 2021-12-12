#pragma once

namespace hackbools { //hackoptions
    //offsets
    bool csgoUpdated = false;

    //menu
    bool menuVisible = true;
    int Instance = 0;
    bool bmenuOpen = true;
    bool init = true;
    bool shouldopen = true;

    //hacks
    bool radarHack = false;
    bool bhHack = false;
    bool flashbangHack = false;


    //aimbot
    namespace aimbot {
        bool aimbothack = false;
        bool targetTeam = false;
        bool targetSight = true;
        float fov = 100;
        float fovAccuracy = 400;
        float fovcolor[4] = {0,0,255,255};
        int selectedbodypart = 3;
        int bodypart = 5;
        bool bfov = true;
        bool drawfov = false;
        bool yawonly = false;
    }
    //triggerbot
    namespace triggerbot {
        bool triggerbothack = false;
        bool targetTeam = false;
        
    }
   
}
namespace offsetload {
    bool placeoutput = true;
    int offset[100];
}