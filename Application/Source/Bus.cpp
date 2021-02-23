#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	grip = 1;
	AddCollider();
	AddPhysics();
	GetPhysics()->SetMass(300);
}

Bus::~Bus()
{
}

void Bus::GameObjectUpdate(double dt)
{
	Vector3 velocity(0, 0, 0);
	float rotation = 0;
	GetPhysics()->SetDrag(1);
	if (Application::IsKeyPressed('T'))
	{
		velocity += GetFoward() * acceleration * dt;
	}
	if (Application::IsKeyPressed('G'))
	{
		velocity -= GetFoward() * acceleration * dt;
	}
	if (Application::IsKeyPressed('F'))
	{
		if (!velocity.IsZero()) rotation += 90 * dt;
	}
	if (Application::IsKeyPressed('H'))
	{
		if (!velocity.IsZero()) rotation -= 90 * dt;
	}
	if (Application::IsKeyPressed('Z'))
	{
		Delete();
	}
	float turnVelMag = 0;
	if (rotation > 0) turnVelMag = (GetPhysics()->GetVelocity() * grip).Length();
	GetPhysics()->AddVelocity(-turnVelMag * GetFoward());
	SetRotateY(GetRotateY() + rotation);
	GetPhysics()->AddVelocity(turnVelMag * GetFoward());
	if (velocity.Length() > acceleration) velocity *= (50 / velocity.Length());
	GetPhysics()->AddVelocity(velocity);
	if (velocity.Length() == 0) GetPhysics()->SetDrag(brakePower);
}

std::string Bus::Type()
{
	return "Bus";
}