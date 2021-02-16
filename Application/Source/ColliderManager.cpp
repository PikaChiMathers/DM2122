#include "ColliderManager.h"
#include"Vector3.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

std::vector<Collider*> ColliderManager::ColliderList;

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

void ColliderManager::RemoveCollider(Collider* col)
{
	for (std::vector<Collider*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) == col)
		{
			ColliderList.erase(it);
			break;
		}
	}
}

Collider* ColliderManager::CheckCollision(Collider* col)
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