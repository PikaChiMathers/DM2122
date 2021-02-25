#include"ColliderObj.h"

ColliderObj::ColliderObj()
{
	AddCollider();
}

ColliderObj::~ColliderObj()
{
}

void ColliderObj::GameObjectUpdate(double dt)
{
	
}

std::string ColliderObj::Type()
{
	return "ColliderObj";
}