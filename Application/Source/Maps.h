#pragma once

#include <string>
#include <vector>
#include <Vector3.h>

struct Maps
{ //Map struct is to change the skybox
    enum class SKYBOX_TYPE
    {
        SB_DAY = 0,
        SB_NIGHT,
        SB_SHOP,
        SB_INTRO,
        NUM_SKYBOX,
    };
    SKYBOX_TYPE skybox;
    std::string skybox_loc[6];
    std::string objs_loc;

    Maps(SKYBOX_TYPE skybox = SKYBOX_TYPE::SB_DAY)
    {   //default constructor
        Set(skybox);
    }

    void Set(SKYBOX_TYPE skybox) 
    {   //Sets the Skybox sides
        this->skybox = skybox;
        //Initialzes the different sides
        skybox_loc[0] = "front.tga";
        skybox_loc[1] = "back.tga";
        skybox_loc[2] = "left.tga";
        skybox_loc[3] = "right.tga";
        skybox_loc[4] = "top.tga";
        skybox_loc[5] = "bottom.tga";

        //Sets up location of the .tga of each side
        std::string location;
        switch (skybox)
        {
        case (SKYBOX_TYPE::SB_DAY):
            location = "Skybox//Day//";
            break;
        case (SKYBOX_TYPE::SB_NIGHT):
            location = "Skybox//Night//";
            break;
        case (SKYBOX_TYPE::SB_SHOP):
            location = "Skybox//Shop//";
            break;
        case (SKYBOX_TYPE::SB_INTRO):
            location = "Skybox//Intro//";  
            break;
        default:
            break;
        }
        //places the location in every element
        for (int side = 0; side < 6; side++)
            skybox_loc[side] = location + skybox_loc[side];
    }
};
