#include "BasicPhysics.h"

BasicPhysics::BasicPhysics(float mass, float drag) : usesGravity(true)
{
	SetMass(mass);
	SetDrag(drag);
}

BasicPhysics::~BasicPhysics()
{
}

void BasicPhysics::SetGravity(bool use)
{
	usesGravity = use;
}

bool BasicPhysics::UsesGravity()
{
	return usesGravity;
}

void BasicPhysics::SetMass(int mass)
{
	this->mass = mass > 0 ? mass : 1;
}

int BasicPhysics::GetMass()
{
	return mass;
}

void BasicPhysics::SetDrag(int drag)
{
	this->drag = drag >= 0 ? drag : 0;
}

int BasicPhysics::GetDrag()
{
	return drag;
}
