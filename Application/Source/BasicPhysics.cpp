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
	this->drag = drag >= 0 ? drag : 1;
}

int BasicPhysics::GetDrag()
{
	return drag;
}

void BasicPhysics::SetVelocity(Vector3 vel)
{
	velocity = vel;
}

void BasicPhysics::AddVelocity(Vector3 vel)
{
	velocity += vel;
}

Vector3 BasicPhysics::GetVelocity()
{
	return velocity;
}

void BasicPhysics::PhysicsUpdate(double dt)
{
	if (velocity.Length() > 0)
	{
		float multiplier = 1.0f - drag * dt;
		if (multiplier < 0) multiplier = 0;
		velocity *= multiplier;
	}
}