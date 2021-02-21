#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	AddCollider();
	AddPhysics();
}

Bus::~Bus()
{
}

void Bus::GameObjectUpdate(double dt)
{
	float xVelocity = 0, zVelocity = 0;
	Vector3 velocity(xVelocity, 0, zVelocity);
	GetPhysics()->SetDrag(1);
	if (Application::IsKeyPressed('T'))
	{
		//zVelocity -= acceleration * dt;
		//GetPhysics()->AddVelocity(GetFoward() * acceleration * dt);
		velocity += GetFoward() * acceleration * dt;
	}
	if (Application::IsKeyPressed('G'))
	{
		//zVelocity += acceleration * dt;
		//GetPhysics()->AddVelocity(GetFoward() * -acceleration * dt);
		velocity -= GetFoward() * acceleration * dt;
	}
	if (Application::IsKeyPressed('F'))
	{
		//xVelocity -= acceleration * dt;
		//GetPhysics()->AddVelocity(GetRight() * -acceleration * dt);
		if (velocity.Length() != 0) SetRotateY(GetRotateY() + 90 * dt);
	}
	if (Application::IsKeyPressed('H'))
	{
		//xVelocity += acceleration * dt;
		//GetPhysics()->AddVelocity(GetRight() * acceleration * dt);
		if (velocity.Length() != 0) SetRotateY(GetRotateY() - 90 * dt);
	}
	if (velocity.Length() > acceleration) velocity *= (50 / velocity.Length());
	GetPhysics()->AddVelocity(velocity);
	if (velocity.Length() == 0) GetPhysics()->SetDrag(brakePower);
}

std::string Bus::Type()
{
	return "Bus";
}