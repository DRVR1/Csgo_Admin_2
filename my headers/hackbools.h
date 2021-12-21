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
    bool autoaccept = false;


    //aimbot
    namespace aimbot {
        int toggleKey = 0x12;
        int speed = 1;
        int newspeed = 10;
        bool aimbothack = false;
        bool targetTeam = false;
        float fov = 100;
        float fovAccuracy = 400;
        float fovcolor[4] = {0,0,255,255};
        int selectedbodypart = 3;
        int bodypart = 5;
        bool bfov = false;
        bool drawfov = false;
        bool yawonly = false;
        bool smoothaim = true;
        bool findnewtarget = true;

        namespace oscillation {
            int antiOscillator = 5;
            bool canDraw = false;
            bool drawOscillator = true;
        }

        //debug shit
        namespace debug {
            bool debugmode = false;
            int gotoX = 0;
            int gotoY = 0;
            int gotoZ = 0;
            int mouseposX = 0;
            int mouseposY = 0;
            int closest = 0;
            int health = 0;
            int iterator = 0;
            int reached = 0;
            int distanceToY = 0;
        }

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