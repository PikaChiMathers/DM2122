#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	AddCollider();
	GetCollider()->AddPhysics();
}

Bus::~Bus()
{
}

void Bus::GameObjectUpdate(double dt)
{
	float xVelocity = 0, zVelocity = 0;
	GetCollider()->GetPhysics()->SetDrag(1);
	if (Application::IsKeyPressed('T'))
	{
		zVelocity -= acceleration * dt;
	}
	if (Application::IsKeyPressed('G'))
	{
		zVelocity += acceleration * dt;
	}
	if (Application::IsKeyPressed('F'))
	{
		xVelocity -= acceleration * dt;
	}
	if (Application::IsKeyPressed('H'))
	{
		xVelocity += acceleration * dt;
	}
	GetCollider()->GetPhysics()->AddVelocity(Vector3(xVelocity, 0, zVelocity));
	if (xVelocity == 0 && zVelocity == 0) GetCollider()->GetPhysics()->SetDrag(brakePower);
}