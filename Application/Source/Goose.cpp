#include"Goose.h"

Goose::Goose()
{
	acceleration = 50;
	AddCollider();
	AddPhysics();
	GetPhysics()->SetMass(300);
}

Goose::~Goose()
{
}

void Goose::GameObjectUpdate(double dt)
{
	GetPhysics()->SetDrag(1000);
	if (Application::IsKeyPressed('S'))
	{
		SetRotateY(0);
		GetPhysics()->SetVelocity(GetFoward() * 5);
	}
	if (Application::IsKeyPressed('W'))
	{
		SetRotateY(180);
		GetPhysics()->SetVelocity(GetFoward() * 5);
	}
	if (Application::IsKeyPressed('A'))
	{
		SetRotateY(-90);
		GetPhysics()->SetVelocity(GetFoward() * 5);
	}
	if (Application::IsKeyPressed('D'))
	{
		SetRotateY(90);
		GetPhysics()->SetVelocity(GetFoward() * 5);
	}
}

std::string Goose::Type()
{
	return "Goose";
}