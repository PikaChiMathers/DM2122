#include "GameObjectManager.h"
#include"GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}
GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); it++)
	{
		delete (*it);
		GameObjectList.erase(it--);
	}
}
//#pragma optimize ("", off)
void GameObjectManager::CreateGameObject(GameObject* gameObject)
{
	GameObjectList.push_back(gameObject);
	if (gameObject->GetCollider() != nullptr) ColliderList.push_back(gameObject);
}

std::vector<GameObject*> GameObjectManager::GetGameObjectList()
{
	return GameObjectList;
}

float GameObjectManager::SATcalculation(Vector3 axis, std::vector<Vector3> points1, std::vector<Vector3> points2)
{
	axis.Normalize();
	float min1, max1, min2, max2;
	min1 = max1 = points1[0].Dot(axis);
	for (std::vector<Vector3>::iterator it_point = points1.begin(); it_point != points1.end(); it_point++)
	{
		float dist = (*it_point).Dot(axis);
		if (dist < min1) min1 = dist;
		if (dist > max1) max1 = dist;
	}
	min2 = max2 = points2[0].Dot(axis);
	for (std::vector<Vector3>::iterator it_point = points2.begin(); it_point != points2.end(); it_point++)
	{
		float dist = (*it_point).Dot(axis);
		if (dist < min2) min2 = dist;
		if (dist > max2) max2 = dist;
	}
	if (min1 < min2)
	{
		if (max1 < min2) return -1;
		return (max1 - min2);
	}
	else // min1 > min 2
	{
		if (max2 < min1) return -1;
		return (max2 - min1);
	}
}

bool GameObjectManager::ListContains(GameObject* obj)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) == obj) return true;
	}
	return false;
}

void GameObjectManager::PushCollider(GameObject* obj)
{
	if (!ListContains(obj))
	{
		ColliderList.push_back(obj);
	}
}

void GameObjectManager::EraseCollider(GameObject* obj)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) == obj)
		{
			ColliderList.erase(it);
			break;
		}
	}
}

Collide GameObjectManager::CheckCollision(Collider* obj)
{
	if (obj == nullptr) return Collide();
	return CheckCollision(*obj, obj);
}

Collide GameObjectManager::CheckCollision(Collider refCol, Collider* exclude)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != exclude && (*it)->GetCollider() != nullptr)
		{
			OBB refColData = refCol.GetOBBData();
			OBB Col2Data = (*it)->GetCollider()->GetOBBData();
			std::vector<Vector3>axes;
			for (std::vector<Vector3>::iterator obbIt = refColData.Axes.begin(); obbIt != refColData.Axes.end(); obbIt++) axes.push_back((*obbIt));
			for (std::vector<Vector3>::iterator obbIt = Col2Data.Axes.begin(); obbIt != Col2Data.Axes.end(); obbIt++) axes.push_back((*obbIt));
			axes.push_back(axes[0].Cross(axes[3]));
			axes.push_back(axes[0].Cross(axes[4]));
			axes.push_back(axes[0].Cross(axes[5]));
			axes.push_back(axes[1].Cross(axes[3]));
			axes.push_back(axes[1].Cross(axes[4]));
			axes.push_back(axes[1].Cross(axes[5]));
			axes.push_back(axes[2].Cross(axes[3]));
			axes.push_back(axes[2].Cross(axes[4]));
			axes.push_back(axes[2].Cross(axes[5]));
			int shortestAxisVec = 0; // stores the iteration of the axis vector that has shortest overlap dist 
			float shortestDist = SATcalculation(axes[0].Normalize(), refColData.Points, Col2Data.Points); // stores the shortest overlap distance
			for (int i = 1; i < axes.size(); i++)
			{
				if (axes[i].IsZero()) continue;
				float dist = SATcalculation(axes[i].Normalize(), refColData.Points, Col2Data.Points);
				if (dist < shortestDist)
				{
					shortestDist = dist;
					shortestAxisVec = i;
				}
				if (dist == -1) break;
			}
			if (shortestDist == -1) continue; // 1 of the axis vectors has no overlap == no collision
			Collide collide;
			collide.gameObject = (*it);
			collide.axis = axes[shortestAxisVec];
			collide.distance = shortestDist;
			return collide;
		}
	}
	return Collide();
}

std::vector<Collide> GameObjectManager::CheckCollisions(Collider* obj)
{
	if (obj == nullptr) return std::vector<Collide>();
	return CheckCollisions(*obj, obj);
}

std::vector<Collide> GameObjectManager::CheckCollisions(Collider refCol, Collider* exclude)
{
	std::vector<Collide>GameObjectsInCollider;
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != exclude && (*it)->GetCollider() != nullptr)
		{
			OBB refColData = refCol.GetOBBData();
			OBB Col2Data = (*it)->GetCollider()->GetOBBData();
			std::vector<Vector3>axes;
			for (std::vector<Vector3>::iterator obbIt = refColData.Axes.begin(); obbIt != refColData.Axes.end(); obbIt++) axes.push_back((*obbIt));
			for (std::vector<Vector3>::iterator obbIt = Col2Data.Axes.begin(); obbIt != Col2Data.Axes.end(); obbIt++) axes.push_back((*obbIt));
			axes.push_back(axes[0].Cross(axes[3]));
			axes.push_back(axes[0].Cross(axes[4]));
			axes.push_back(axes[0].Cross(axes[5]));
			axes.push_back(axes[1].Cross(axes[3]));
			axes.push_back(axes[1].Cross(axes[4]));
			axes.push_back(axes[1].Cross(axes[5]));
			axes.push_back(axes[2].Cross(axes[3]));
			axes.push_back(axes[2].Cross(axes[4]));
			axes.push_back(axes[2].Cross(axes[5]));
			int shortestAxisVec = 0; // stores the iteration of the axis vector that has shortest overlap dist 
			float shortestDist = SATcalculation(axes[0].Normalize(), refColData.Points, Col2Data.Points); // stores the shortest overlap distance
			for (int i = 1; i < axes.size(); i++)
			{
				if (axes[i].IsZero()) continue;
				float dist = SATcalculation(axes[i].Normalize(), refColData.Points, Col2Data.Points);
				if (dist < shortestDist)
				{
					shortestDist = dist;
					shortestAxisVec = i;
				}
				if (dist == -1) break;
			}
			if (shortestDist == -1) continue; // 1 of the axis vectors has no overlap == no collision
			Collide collide;
			collide.gameObject = (*it);
			collide.axis = axes[shortestAxisVec];
			collide.distance = shortestDist;
			GameObjectsInCollider.push_back(collide);
		}
	}
	return GameObjectsInCollider;
}

void GameObjectManager::GameObjectManagerUpdate(double dt)
{
	for (std::vector<GameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); it++)
	{
		if ((*it)->GetDelete())
		{
			GameObjectList.erase(it);
			continue;
		}
		(*it)->GameObjectUpdate(dt);

		if ((*it)->GetCollider() != nullptr)
		{
			if (!ListContains((*it))) ColliderList.push_back((*it));
			GameObject* gameObject = (*it);
			if (gameObject->GetCollider()->GetIsTrigger()) // Check for Trigger Collider Objects
			{
				std::vector<Collide>CheckTrigger = CheckCollisions(gameObject->GetCollider());
				for (std::vector<GameObject*>::iterator it = gameObject->InTrigger.begin(); it != gameObject->InTrigger.end(); it++)
				{
					bool notMatched = true;
					for (std::vector<Collide>::iterator itNew = CheckTrigger.begin(); itNew != CheckTrigger.end(); itNew++)
					{
						if ((*it) == (*itNew).gameObject)
						{
							gameObject->OnTriggerStay((*itNew).gameObject);
							CheckTrigger.erase(itNew);
							notMatched = false;
							break;
						}
					}
					if (notMatched)
					{
						gameObject->OnTriggerExit((*it));
						gameObject->InTrigger.erase(it--);
					}
				}
				for (std::vector<Collide>::iterator it = CheckTrigger.begin(); it != CheckTrigger.end(); it++)
				{
					gameObject->OnTriggerEnter((*it).gameObject);
					gameObject->InTrigger.push_back((*it).gameObject);
				}
			}
			if (gameObject->GetPhysics() != nullptr && !gameObject->GetCollider()->GetIsTrigger()) // check for collision
			{
				BasicPhysics* physics = gameObject->GetPhysics();
				if (physics->GetVelocity().Length() > 0)
				{
					Position newPos(gameObject->GetPositionX() + physics->GetVelocity().x * dt, gameObject->GetPositionY() + physics->GetVelocity().y * dt, gameObject->GetPositionZ() + physics->GetVelocity().z * dt);

					Collider RefCollider;
					RefCollider.SetTransform(gameObject->GetCollider()->GetTransform());
					RefCollider.SetSize(gameObject->GetCollider()->GetSize());
					RefCollider.SetPosition(newPos);
					Collide hit = CheckCollision(RefCollider, gameObject->GetCollider());
					if (hit.gameObject != nullptr && !hit.gameObject->GetCollider()->GetIsTrigger())
					{
						float posGO, pos2;
						Vector3 axis = hit.axis.Normalize();
						posGO = Vector3(newPos.x, newPos.y, newPos.z).Dot(axis);
						pos2 = Vector3(hit.gameObject->GetPositionX(), hit.gameObject->GetPositionY(), hit.gameObject->GetPositionZ()).Dot(axis);
						axis *= hit.distance * (posGO > pos2 ? 1 : -1);
						Vector3 translatePos(newPos.x, newPos.y, newPos.z);
						translatePos += axis;
						newPos.Set(translatePos.x, translatePos.y, translatePos.z);
						axis = hit.axis.Normalize();
						physics->AddVelocity(axis * -physics->GetVelocity().Dot(axis));
					}
					gameObject->SetPosition(newPos);
					//{ // physics stuff not working
						//BasicPhysics* hitPhysics = hit->GetCollider()->GetPhysics();
						///***********************************
						//formula: 
						//v1f = ( (m1 - m2)u1 + 2m2 u2 ) / m1 + m2
						//v2f = ( (m2 - m1)u2 + 2m1 u1 ) / m1 + m2
						//************************************/
						//physics->SetVelocity(((physics->GetMass() - hitPhysics->GetMass()) * physics->GetVelocity() + 2 * hitPhysics->GetMass() * hitPhysics->GetVelocity()) * (1 / (physics->GetMass() + hitPhysics->GetMass())));
						//hitPhysics->SetVelocity(((hitPhysics->GetMass() - physics->GetMass()) * hitPhysics->GetVelocity() + 2 * physics->GetMass() * physics->GetVelocity()) * (1 / (physics->GetMass() + hitPhysics->GetMass())));
						//colliding = false;
						//break;
					//}
					physics->PhysicsUpdate(dt);					
				}
			}
		}
		else if (ListContains((*it)))
		{
			ColliderList.erase(it);
		}
	}
}
#pragma optimize ("", on)
