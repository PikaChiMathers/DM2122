#include "Collider.h"

Collider::Collider()
{
}

Collider::~Collider()
{
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
