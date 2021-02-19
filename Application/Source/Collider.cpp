#include "Collider.h"

Collider::Collider()
{
	isTrigger = false;
}

Collider::Collider(Position position, Size size) : position(position), size(size)
{
	isTrigger = false;
}

Collider::~Collider()
{
	//Nothing. 
}

void Collider::SetPosition(Position pos)
{
	position = pos;
}

void Collider::SetRotation(Rotation rot)
{
	rotation = rot;
}

void Collider::SetSize(Size size)
{
	this->size = size;
}

Position Collider::GetPosition()
{
	return position;
}

Rotation Collider::GetRotation()
{
	return rotation;
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