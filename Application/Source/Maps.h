#pragma once

#include <string>

struct Maps
{ //Map struct is to change the skybox and objs in map depending on map_type
    enum class MAP_TYPE
    {
        MAP_CITY = 0,
        NUM_MAPS,
    };

    MAP_TYPE type;
    std::string objs_loc;

    Maps(MAP_TYPE type = MAP_TYPE::MAP_CITY)
    {
        Set(type);
    }

    void Set(MAP_TYPE type)
    {
        this->type = type;

        std::string location;
        switch (type)
        {
        case (MAP_TYPE::MAP_CITY): 
            break;
        default:
            break;
        }
    }
};
