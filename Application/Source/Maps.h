#pragma once

#include <string>

struct Maps
{ //Map struct is to change the skybox and objs in map depending on map_type
    enum class MAP_TYPE
    {
        M_DAY = 0,
        M_NIGHT,
        NUM_MAPS,
    };

    MAP_TYPE type;
    std::string skybox_loc[6];
    std::string objs_loc;

    Maps(MAP_TYPE type = MAP_TYPE::M_DAY)
    {
        Set(type);
    }

    void Set(MAP_TYPE type)
    {
        this->type = type;
        skybox_loc[0] = "front.tga";
        skybox_loc[1] = "back.tga";
        skybox_loc[2] = "left.tga";
        skybox_loc[3] = "right.tga";
        skybox_loc[4] = "top.tga";
        skybox_loc[5] = "bottom.tga";
        std::string location;
        switch (type)
        {
        case (MAP_TYPE::M_DAY):
            location = "Maps//City//Day//Skybox//";
            break;
        case (MAP_TYPE::M_NIGHT):
            location = "Maps//City//Night//Skybox//";
            break;

        default:
            break;
        }

        for (int side = 0; side < 6; side++)
            skybox_loc[side] = location + skybox_loc[side];
    }
};
