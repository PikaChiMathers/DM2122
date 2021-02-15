#pragma once

#include <string>

struct Maps
{ //Map struct is to change the skybox and objs in map depending on map_type
	enum MAP_TYPE
	{
		MAP_CITY,
		NUM_MAPS,
	};

	MAP_TYPE type;
	std::string skybox_loc;
	std::string objs_loc;

	Maps(MAP_TYPE type = MAP_CITY)
	{
		Set(type);
	}

	void Set(MAP_TYPE type)
	{
		this->type = type;
		switch (type)
		{
		case 0:
			skybox_loc = "Image//";
			break;
		default:
			skybox_loc = "Image//";
			break;
		}
	}
};
