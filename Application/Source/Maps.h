#pragma once

#include <string>
#include <vector>
#include <Vector3.h>

struct Maps
{ //Map struct is to change the environment depending on the skybox and map type
    enum class SKYBOX_TYPE
    {
        SB_DAY = 0,
        SB_NIGHT,
        NUM_SKYBOX,
    };

    enum class MAP_TYPE
    {
        M_CITY = 0,
        M_TRIVIA,
        NUM_MAPS,
    };

    MAP_TYPE type;
    SKYBOX_TYPE skybox;
    std::string skybox_loc[6];
    std::string objs_loc;

    Maps(MAP_TYPE type = MAP_TYPE::M_CITY, SKYBOX_TYPE skybox = SKYBOX_TYPE::SB_DAY)
    {   //default constructor
        Set(type, skybox);
    }

    void Set(MAP_TYPE type, SKYBOX_TYPE skybox)
    {   //Sets the map type and skybox type
        this->type = type;
        this->skybox = skybox;

        Set(skybox);
    }

    void Set(SKYBOX_TYPE skybox) 
    {   //Sets the Skybox sides

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
            location = "Maps//City//Day//Skybox//";
            break;
        case (SKYBOX_TYPE::SB_NIGHT):
            location = "Maps//City//Night//Skybox//";
            break;

        default:
            break;
        }
        //places the location in every element
        for (int side = 0; side < 6; side++)
            skybox_loc[side] = location + skybox_loc[side];
    }
};
