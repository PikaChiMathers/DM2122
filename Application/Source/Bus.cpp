#include"Bus.h"

Bus::Bus()
{
	moneyCurrent = 0;
	passengers = 0;
	acceleration = 50;
	brakePower = 5;
	stop = false;
	overSteerPct = 0;
	SetScale(Scale(3, 3, 12));
	AddCollider();
	AddPhysics();
	GetPhysics()->SetMass(300);

	loopDelay = 0;
}

int Bus::money;

Bus::~Bus()
{
	//Nothing.
}

void Bus::SetMoney(int amount)
{
	Bus::money = amount;
}

void Bus::AddMoney(int amount)
{
	Bus::money += amount;
}

int Bus::GetMoney()
{
	return Bus::money;
}

void Bus::SetPassengerCount(int count)
{
	passengers = count;
}

void Bus::AddPassengerCount()
{
	passengers++;
}

int Bus::GetPassengerCount()
{
	return passengers;
}

void Bus::SetAccel(float accel)
{
	acceleration = accel;
}

void Bus::SetBrakePower(float brake)
{
	brakePower = brake;
}

void Bus::SetStop(bool stop)
{
	this->stop = stop;
}

void Bus::GameObjectUpdate(double dt)
{
	if (!stop)
	{
		SetPositionY(0); // fix y position
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
			if (GetPhysics()->GetVelocity().Dot(GetFoward()) > 8) rotation += 90 * dt;
			else if (GetPhysics()->GetVelocity().Dot(GetFoward()) < -8) rotation -= 90 * dt;
		}
		if (Application::IsKeyPressed('H'))
		{
			if (GetPhysics()->GetVelocity().Dot(GetFoward()) > 8) rotation -= 90 * dt;
			else if (GetPhysics()->GetVelocity().Dot(GetFoward()) < -8) rotation += 90 * dt;
		}
		if (Application::IsKeyPressed('X'))
		{
			overSteerPct = 0;
		}
		else overSteerPct = overSteerPct < 1 ? overSteerPct + dt : 1;

		if (velocity.IsZero())
		{
			GetPhysics()->SetDrag(brakePower);
			//if can try put sound for braking here. this will keep looping so make it only play once
		}
		else
		{
			SetRotateY(GetRotateY() + rotation);
			float centripetalForce = GetPhysics()->GetVelocity().Dot(GetRight()) * overSteerPct; // simulate tire grip
			GetPhysics()->AddVelocity(GetRight() * -centripetalForce);

			if (velocity.Length() > acceleration) velocity *= (50 / velocity.Length()); // cap velocity
			GetPhysics()->AddVelocity(velocity);

			if (loopDelay <= 0) // for sound
			{
				//sound.Engine()->play2D("media/bus.wav"); // this loud af
				loopDelay = 2.5;
			}
			else loopDelay -= dt;
		}
	}
}

std::string Bus::Type()
{
	return "Bus";
}