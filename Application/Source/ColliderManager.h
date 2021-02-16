#pragma once
#ifndef COLLIDERMANAGER_H
#define COLLIDERMANAGER_H

#include "Collider.h"
#include <vector>

class ColliderManager
{
	static std::vector<Collider*>ColliderList;
public:
	ColliderManager();
	~ColliderManager();
	static bool ListContains(Collider* col);
	static void PushCollider(Collider* col);
	static Collider* checkCollision(Collider* col);
};
#endif