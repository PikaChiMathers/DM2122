#pragma once
#ifndef COLLIDEROBJECT_H
#define COLLIDEROBJECT_H

#include"GameObject.h"

class ColliderObj : public GameObject
{
public:
	ColliderObj();
	~ColliderObj();
	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif