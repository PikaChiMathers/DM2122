#include"GameObject.h"

std::vector<GameObject*> GameObject::GameObjectList;
GameObject::GameObject()
{
	collider = nullptr;
	physics = nullptr;
	GameObjectList.push_back(this);
}

GameObject::~GameObject()
{
	RemoveCollider();
	RemovePhysics();
	for (std::vector<GameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); it++)
	{
		if ((*it) == this)
		{
			GameObjectList.erase(it);
			break;
		}
	}
}

void GameObject::SetPositionX(float x) { transform.position.x = x; ColliderUpdate(); }
void GameObject::SetPositionY(float y) { transform.position.y = y; ColliderUpdate(); }
void GameObject::SetPositionZ(float z) { transform.position.z = z; ColliderUpdate(); }
void GameObject::SetPosition(Position pos) { transform.position = pos; ColliderUpdate(); }
float GameObject::GetPositionX() { return transform.position.x; }
float GameObject::GetPositionY() { return transform.position.y; }
float GameObject::GetPositionZ() { return transform.position.z; }
Position GameObject::GetPosition() { return transform.position; }

void GameObject::SetRotateX(float x) { transform.rotation.x = x; transform.UpdateDirectionVectors(); ColliderUpdate(); }
void GameObject::SetRotateY(float y) { transform.rotation.y = y; transform.UpdateDirectionVectors(); ColliderUpdate(); }
void GameObject::SetRotateZ(float z) { transform.rotation.z = z; transform.UpdateDirectionVectors(); ColliderUpdate(); }
void GameObject::SetRotate(Rotation rot) { transform.rotation = rot; transform.UpdateDirectionVectors(); ColliderUpdate(); }
float GameObject::GetRotateX() { return transform.rotation.x; }
float GameObject::GetRotateY() { return transform.rotation.y; }
float GameObject::GetRotateZ() { return transform.rotation.z; }
Rotation GameObject::GetRotate() { return transform.rotation; }

void GameObject::SetScaleX(float x) { transform.scale.x = x; ColliderUpdate(); }
void GameObject::SetScaleY(float y) { transform.scale.y = y; ColliderUpdate(); }
void GameObject::SetScaleZ(float z) { transform.scale.z = z; ColliderUpdate(); }
void GameObject::SetScale(Scale scale) { transform.scale = scale; ColliderUpdate(); }
float GameObject::GetScaleX() { return transform.scale.x; }
float GameObject::GetScaleY() { return transform.scale.y; }
float GameObject::GetScaleZ() { return transform.scale.z; }
Scale GameObject::GetScale() { return transform.scale; }

Vector3 GameObject::GetFoward()
{
	return transform.foward;
}

Vector3 GameObject::GetUp()
{
	return transform.up;
}

Vector3 GameObject::GetRight()
{
	return transform.right;
}

void GameObject::AddCollider()
{
	if (collider == nullptr)
	{
		collider = new Collider();
		GameObject::PushCollider(this);
		ColliderUpdate();
	}
}

void GameObject::RemoveCollider()
{
	if (collider != nullptr)
	{
		GameObject::EraseCollider(this);
		delete collider;
		collider = nullptr;
	}
}

Collider* GameObject::GetCollider()
{
	return collider;
}

void GameObject::ColliderUpdate()
{
	if (collider != nullptr)
	{
		collider->SetTransform(transform);
		collider->SetSize(Size(transform.scale.x, transform.scale.y, transform.scale.z));
	}
}

void GameObject::AddPhysics()
{
	if (physics == nullptr)
		physics = new BasicPhysics();
}

BasicPhysics* GameObject::GetPhysics()
{
	return physics;
}

void GameObject::RemovePhysics()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}

void GameObject::SetTag(std::string tag)
{
	this->tag = tag;
}

std::string GameObject::GetTag()
{
	return tag;
}

void GameObject::GameObjectUpdate(double dt)
{
	
}

std::string GameObject::Type()
{
	return "Base";
}

void GameObject::OnTriggerEnter(GameObject* gameObject)
{
	
}

void GameObject::OnTriggerStay(GameObject* gameObject)
{

}

void GameObject::OnTriggerExit(GameObject* gameObject)
{

}

/**************************************************/
//Collider/physics Update area
/**************************************************/
std::vector<GameObject*> GameObject::ColliderList;
float GameObject::SATcalculation(Vector3 axis, std::vector<Vector3> points1, std::vector<Vector3> points2)
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

bool GameObject::ListContains(GameObject* obj)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it) == obj) return true;
	}
	return false;
}

void GameObject::PushCollider(GameObject* obj)
{
	if (!ListContains(obj))
	{
		ColliderList.push_back(obj);
	}
}

void GameObject::EraseCollider(GameObject* obj)
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

Collide GameObject::CheckCollision(Collider* obj)
{
	if (obj == nullptr) return Collide();
	return CheckCollision(*obj, obj);
}

Collide GameObject::CheckCollision(Collider refCol, Collider* exclude)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != exclude)
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
			float shortestDist = 100000000;
			shortestDist = GameObject::SATcalculation(axes[0].Normalize(), refColData.Points, Col2Data.Points); // stores the shortest overlap distance
			for (int i = 1; i < axes.size(); i++)
			{
				if (axes[i].IsZero()) continue;
				float dist = GameObject::SATcalculation(axes[i].Normalize(), refColData.Points, Col2Data.Points);
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

std::vector<Collide> GameObject::CheckCollisions(Collider* obj)
{
	if (obj == nullptr) return std::vector<Collide>();
	return CheckCollisions(*obj, obj);
}

std::vector<Collide> GameObject::CheckCollisions(Collider refCol, Collider* exclude)
{
	std::vector<Collide>GameObjectsInCollider;
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != exclude)
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
			float shortestDist = 100000000;
			shortestDist = GameObject::SATcalculation(axes[0].Normalize(), refColData.Points, Col2Data.Points); // stores the shortest overlap distance
			for (int i = 1; i < axes.size(); i++)
			{
				if (axes[i].IsZero()) continue;
				float dist = GameObject::SATcalculation(axes[i].Normalize(), refColData.Points, Col2Data.Points);
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


void GameObject::GameObjectUpdateManager(double dt)
{
	for (std::vector<GameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); it++)
	{
		(*it)->GameObjectUpdate(dt);
		if ((*it)->GetCollider() != nullptr)
		{
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
						gameObject->InTrigger.erase(it);
					}
				}
				for (std::vector<Collide>::iterator it = CheckTrigger.begin(); it != CheckTrigger.end(); it++)
				{
					gameObject->OnTriggerEnter((*it).gameObject);
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
					RefCollider.GetTransform().position = newPos;
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
	}
}