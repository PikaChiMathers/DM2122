#pragma once
#ifndef COLLIDERMANAGER_H
#define COLLIDERMANAGER_H

#include "Collider.h"
#include <vector>

class ColliderManager
{
	std::vector<Collider*>ColliderList;
public:
	ColliderManager();
	~ColliderManager();
	bool ListContains(Collider* col);
	void PushCollider(Collider* col);
	Collider* checkCollision(Collider* col);
};
#endif