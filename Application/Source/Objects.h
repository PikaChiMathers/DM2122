#pragma once
#ifndef OBJECTS_H
#define OBJECTS_H

#include"GameObject.h"

class Objects : public GameObject
{
public:
	Objects();
	~Objects();

	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif