#include "Collider.h"

Collider::Collider()
{
	isTrigger = false;
}

Collider::~Collider()
{
	//Nothing. 
}

void Collider::SetPosition(Position pos)
{
	transform.position = pos;
}

void Collider::SetRotation(Rotation rot)
{
	transform.rotation = rot;
}

void Collider::SetTransform(Transform transform)
{
	this->transform = transform;
}

void Collider::SetSize(Size size)
{
	this->size = size;
}

Position Collider::GetPosition()
{
	return transform.position;
}

Rotation Collider::GetRotation()
{
	return transform.rotation;
}

Transform Collider::GetTransform()
{
	return transform;
}

Size Collider::GetSize()
{
	return size;
}

void Collider::SetIsTrigger(bool IsTrigger)
{
	this->isTrigger = IsTrigger;
}

bool Collider::GetIsTrigger()
{
	return isTrigger;
}

OBB Collider::GetOBBData()
{
    OBB data;
    Vector3 Center(GetPosition().x, GetPosition().y, GetPosition().z);

    ///**
    //* bottom corner 0 0 0
    //* top corner 1 1 -1
    //*/
    //data.Points.push_back(Center += -GetTransform().foward * (GetSize().z * 0.5f) - GetTransform().up * (GetSize().y * 0.5f) - GetTransform().right * (GetSize().x * 0.5f));
    //data.Points.push_back(Center += GetTransform().foward * (GetSize().z * 0.5f) + GetTransform().up * (GetSize().y * 0.5f) + GetTransform().right * (GetSize().x * 0.5f));

    /**
    * 0 0 0,
    * 0 0 1,
    * 0 1 0,
    * 1 0 0,
    * 1 0 1,
    * 1 1 1,
    * 0 1 1,
    * 1 1 0,
    */
    data.Points.push_back(Center - GetTransform().foward * (GetSize().z * 0.5f) - GetTransform().up * (GetSize().y * 0.5f) - GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center + GetTransform().foward * (GetSize().z * 0.5f) - GetTransform().up * (GetSize().y * 0.5f) - GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center - GetTransform().foward * (GetSize().z * 0.5f) + GetTransform().up * (GetSize().y * 0.5f) - GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center - GetTransform().foward * (GetSize().z * 0.5f) - GetTransform().up * (GetSize().y * 0.5f) + GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center + GetTransform().foward * (GetSize().z * 0.5f) - GetTransform().up * (GetSize().y * 0.5f) + GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center + GetTransform().foward * (GetSize().z * 0.5f) + GetTransform().up * (GetSize().y * 0.5f) + GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center + GetTransform().foward * (GetSize().z * 0.5f) + GetTransform().up * (GetSize().y * 0.5f) - GetTransform().right * (GetSize().x * 0.5f));
    data.Points.push_back(Center - GetTransform().foward * (GetSize().z * 0.5f) + GetTransform().up * (GetSize().y * 0.5f) + GetTransform().right * (GetSize().x * 0.5f));

    /**
    * Foward axis -Z
    * Up axis +Y
    * Right axis +X
    */
    data.Axes.push_back(GetTransform().foward);
    data.Axes.push_back(GetTransform().up);
    data.Axes.push_back(GetTransform().right);

    return data;
}
