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
	for (std::vector<GameObject*>::iterator it = ColliderList.begin(); it != ColliderList.end(); it++)
	{
		if ((*it)->GetCollider() != obj)
		{
			if (abs((*it)->GetCollider()->GetPosition().x - obj->GetPosition().x) < ((*it)->GetCollider()->GetSize().x + obj->GetSize().x) * 0.5f &&
				abs((*it)->GetCollider()->GetPosition().y - obj->GetPosition().y) < ((*it)->GetCollider()->GetSize().y + obj->GetSize().y) * 0.5f &&
				abs((*it)->GetCollider()->GetPosition().z - obj->GetPosition().z) < ((*it)->GetCollider()->GetSize().z + obj->GetSize().z) * 0.5f)
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
		if (gameObject->GetCollider()->GetPhysics() != nullptr)
		{
			BasicPhysics* physics = gameObject->GetCollider()->GetPhysics();
			if (physics->GetVelocity().Length() > 0)
			{
				physics->PhysicsUpdate(dt);
				gameObject->SetPosition(Position(gameObject->GetPositionX() + physics->GetVelocity().x, gameObject->GetPositionY() + physics->GetVelocity().y, gameObject->GetPositionZ() + physics->GetVelocity().z));
			}
		}
	}
}