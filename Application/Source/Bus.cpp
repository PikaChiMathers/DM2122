#include"Bus.h"

Bus::Bus()
{
	acceleration = 50;
	brakePower = 5;
	stop = false;
	overSteerPct = 0;
	SetScale(Scale(1, 1, 4));
	AddCollider();
	AddPhysics();
	GetPhysics()->SetMass(300);
}

Bus::~Bus()
{
}

void Bus::setStop(bool stop)
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
		if (GetPhysics()->GetVelocity().Dot(GetFoward()) > 0) rotation += 90 * dt;
		else if (GetPhysics()->GetVelocity().Dot(GetFoward()) < 0) rotation -= 90 * dt;
	}
	if (Application::IsKeyPressed('H'))
	{
		if (GetPhysics()->GetVelocity().Dot(GetFoward()) > 0) rotation -= 90 * dt;
		else if (GetPhysics()->GetVelocity().Dot(GetFoward()) < 0) rotation += 90 * dt;
	}
	if (Application::IsKeyPressed('X'))
	{
		overSteerPct = 0;
	}
	else overSteerPct = overSteerPct < 1 ? overSteerPct + dt : 1;

	if (velocity.IsZero()) GetPhysics()->SetDrag(brakePower);
	else
	{
		SetRotateY(GetRotateY() + rotation);
		float centripetalForce = GetPhysics()->GetVelocity().Dot(GetRight()) * overSteerPct; // simulate tire grip
		GetPhysics()->AddVelocity(GetRight() * -centripetalForce);

		if (velocity.Length() > acceleration) velocity *= (50 / velocity.Length()); // cap velocity
		GetPhysics()->AddVelocity(velocity);
	}
}

std::string Bus::Type()
{
	return "Bus";
}