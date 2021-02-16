#include "ColliderManager.h"
#include"Vector3.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

bool ColliderManager::ListContains(Collider* col)
{
	for (std::vector<Collider*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) == col) return true;
	}
	return false;
}

void ColliderManager::PushCollider(Collider* col)
{
	if (!ListContains(col))
	{
		ColliderList.push_back(col);
	}
}

Collider* ColliderManager::checkCollision(Collider* col)
{
	for (std::vector<Collider*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) != col)
		{
			if (abs((*it)->GetPosition().x - col->GetPosition().x) < ((*it)->GetSize().x + col->GetSize().x) * 0.5f &&
				abs((*it)->GetPosition().y - col->GetPosition().y) < ((*it)->GetSize().y + col->GetSize().y) * 0.5f &&
				abs((*it)->GetPosition().z - col->GetPosition().z) < ((*it)->GetSize().z + col->GetSize().z) * 0.5f)
			{
				return (*it);
			}
		}
	}
	return nullptr;
}