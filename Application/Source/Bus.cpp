#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	AddCollider();
	GetCollider()->AddPhysics();
	GetCollider()->GetPhysics()->SetDrag(1);
}

Bus::~Bus()
{
}

void Bus::moveFoward()
{
	GetCollider()->GetPhysics()->AddVelocity(Vector3(0, 0, 1) * acceleration);
}

void Bus::moveBackward()
{
	GetCollider()->GetPhysics()->AddVelocity(Vector3(0, 0, 1) * -acceleration);
}

void Bus::moveLeft()
{
	GetCollider()->GetPhysics()->AddVelocity(Vector3(1, 0, 0) * acceleration);
}

void Bus::moveRight()
{
	GetCollider()->GetPhysics()->AddVelocity(Vector3(1, 0, 0) * acceleration);
}
