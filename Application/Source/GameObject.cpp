#include"GameObject.h"

GameObject::GameObject()
{
	collider = nullptr;
}

GameObject::~GameObject()
{
	RemoveCollider();
}

void GameObject::SetPositionX(float x) { transform.position.x = x; ColliderUpdate(); }
void GameObject::SetPositionY(float y) { transform.position.y = y; ColliderUpdate(); }
void GameObject::SetPositionZ(float z) { transform.position.z = z; ColliderUpdate(); }
void GameObject::SetPosition(Position pos) { transform.position = pos; ColliderUpdate(); }
float GameObject::GetPositionX() { return transform.position.x; }
float GameObject::GetPositionY() { return transform.position.y; }
float GameObject::GetPositionZ() { return transform.position.z; }
Position GameObject::GetPosition() { return transform.position; }

void GameObject::SetRotateX(float x) { transform.rotation.x = x; }
void GameObject::SetRotateY(float y) { transform.rotation.y = y; }
void GameObject::SetRotateZ(float z) { transform.rotation.z = z; }
void GameObject::SetRotate(Rotation rot) { transform.rotation = rot; }
float GameObject::GetRotateX() { return transform.rotation.x; }
float GameObject::GetRotateY() { return transform.rotation.y; }
float GameObject::GetRotateZ() { return transform.rotation.z; }
Rotation GameObject::GetRotate() { return transform.rotation; }

void GameObject::SetScaleX(float x) { transform.scale.x = x; }
void GameObject::SetScaleY(float y) { transform.scale.y = y; }
void GameObject::SetScaleZ(float z) { transform.scale.z = z; }
void GameObject::SetScale(Scale scale) { transform.scale = scale; }
float GameObject::GetScaleX() { return transform.scale.x; }
float GameObject::GetScaleY() { return transform.scale.y; }
float GameObject::GetScaleZ() { return transform.scale.z; }
Scale GameObject::GetScale() { return transform.scale; }

void GameObject::AddCollider()
{
	if (collider == nullptr)
	{
		collider = new Collider();
		GameObject::PushCollider(this);
	}
}

void GameObject::RemoveCollider()
{
	if (collider != nullptr)
	{
		GameObject::RemoveCollider(this);
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
		collider->SetPosition(transform.position);
	}
}

/**************************************************/
//Collider/physics Update area
/**************************************************/
std::vector<GameObject*> GameObject::ColliderList;

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

void GameObject::RemoveCollider(GameObject* obj)
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

GameObject* GameObject::CheckCollision(Collider* obj)
{
	if (obj == nullptr) return nullptr;
	return CheckCollision(obj->GetPosition(), obj->GetSize(), obj);
}

GameObject* GameObject::CheckCollision(Position pos, Size size, Collider* exclude)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != exclude)
		{
			if (abs((*it)->GetCollider()->GetPosition().x - pos.x) < ((*it)->GetCollider()->GetSize().x + size.x) * 0.5f &&
				abs((*it)->GetCollider()->GetPosition().y - pos.y) < ((*it)->GetCollider()->GetSize().y + size.y) * 0.5f &&
				abs((*it)->GetCollider()->GetPosition().z - pos.z) < ((*it)->GetCollider()->GetSize().z + size.z) * 0.5f)
			{
				return (*it);
			}
		}
	}
	return nullptr;
}

void GameObject::GameObjectUpdate(double dt)
{
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		GameObject* gameObject = (*it);
		if (gameObject->GetCollider()->GetPhysics() != nullptr && !gameObject->GetCollider()->GetIsTrigger())
		{
			BasicPhysics* physics = gameObject->GetCollider()->GetPhysics();
			if (physics->GetVelocity().Length() > 0)
			{
				Position newPos(gameObject->GetPositionX() + physics->GetVelocity().x * dt, gameObject->GetPositionY() + physics->GetVelocity().y * dt, gameObject->GetPositionZ() + physics->GetVelocity().z * dt);
				bool colliding = true;
				for (int i = 0; i < 5; i++) // if after 5 attempts to get the obj out of other colliders and still fail, just dont move it.
				{
					GameObject* hit = CheckCollision(newPos, gameObject->GetCollider()->GetSize(), gameObject->GetCollider());
					if (hit == nullptr || hit->GetCollider()->GetIsTrigger())
					{
						colliding = false;
						break;
					}
					//if (hit->GetCollider()->GetPhysics() == nullptr)
					{
						float xDif = (gameObject->GetCollider()->GetSize().x + hit->GetCollider()->GetSize().x) * .5f - abs(newPos.x - hit->GetPositionX());
						float yDif = (gameObject->GetCollider()->GetSize().y + hit->GetCollider()->GetSize().y) * .5f - abs(newPos.y - hit->GetPositionY());
						float zDif = (gameObject->GetCollider()->GetSize().z + hit->GetCollider()->GetSize().z) * .5f - abs(newPos.z - hit->GetPositionZ());
						if (xDif < yDif && xDif < zDif)
						{
							newPos.x += newPos.x > hit->GetPositionX() ? xDif : -xDif;
						}
						else if (yDif < zDif)
						{
							newPos.y += newPos.y > hit->GetPositionY() ? yDif : -yDif;
						}
						else
						{
							newPos.z += newPos.z > hit->GetPositionZ() ? zDif : -zDif;
						}
					}
					//else
					//{
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
				}
				if (colliding)
				{
					std::cout << "cant get out\n";
				}
				else
				{
					gameObject->SetPosition(newPos);
				}
				physics->PhysicsUpdate(dt);
			}
		}
	}
}