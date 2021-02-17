#include "Collider.h"

Collider::Collider()
{
	physics = nullptr;
	isTrigger = false;
}

Collider::Collider(Position position, Size size) : position(position), size(size)
{
	physics = nullptr;
	isTrigger = false;
}

Collider::~Collider()
{
	RemovePhysics();
}

void Collider::SetPosition(Position pos)
{
	position = pos;
}

void Collider::SetSize(Size size)
{
	this->size = size;
}

Position Collider::GetPosition()
{
	return position;
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

void Collider::AddPhysics()
{
	if (physics == nullptr)
	physics = new BasicPhysics();
}

BasicPhysics* Collider::GetPhysics()
{
	return physics;
}

void Collider::RemovePhysics()
{
	if (physics != nullptr)
	{
		delete physics;
		physics = nullptr;
	}
}