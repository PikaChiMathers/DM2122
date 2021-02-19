#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	AddCollider();
	GetCollider()->AddPhysics();
	SetPosition(Position(1, 0, 10));
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
	Vector3 velocity(xVelocity, 0, zVelocity);
	if (velocity.Length() > acceleration) velocity* (50 / velocity.Length());
	GetCollider()->GetPhysics()->AddVelocity(Vector3(xVelocity, 0, zVelocity));
	if (xVelocity == 0 && zVelocity == 0) GetCollider()->GetPhysics()->SetDrag(brakePower);
}

std::string Bus::Type()
{
	return "Bus";
}