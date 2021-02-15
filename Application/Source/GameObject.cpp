#include"GameObject.h"

GameObject::GameObject()
{
	collider = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::SetPositionX(float x) { transform.position.x = x; }
void GameObject::SetPositionY(float y) { transform.position.y = y; }
void GameObject::SetPositionZ(float z) { transform.position.z = z; }
void GameObject::SetPosition(Position pos) { transform.position = pos; }
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