#include"DriveObjective.h"

DriveObjective::DriveObjective()
{
	player = nullptr;
	requiredPassengerCount = 10;
	pause = true;
	timer = 60;
	//AddCollider();
	//GetCollider()->SetIsTrigger(true);
}

DriveObjective::~DriveObjective()
{
	//Nothing.
}

void DriveObjective::SetPlayer(Bus* player)
{
	this->player = player;
}

void DriveObjective::SetReqiuredPassengerCount(int count)
{
	requiredPassengerCount = count;
}

int DriveObjective::GetRequiredPassengerCount()
{
	return requiredPassengerCount;
}

void DriveObjective::SetTimer(double timer)
{
	this->timer = timer;
}

void DriveObjective::StartTimer()
{
	pause = false;
}

void DriveObjective::PauseTimer()
{
	pause = true;
}

double DriveObjective::GetTime()
{
	return timer;
}

void DriveObjective::GameObjectUpdate(double dt)
{
	if (!pause) timer -= dt;
	player->SetStop(pause);
	if (timer <= 0)
	{
		player->SetStop(true);
		// end the game
	}
}

void DriveObjective::OnTriggerStay(GameObject* gameObject)
{
	//if (gameObject != nullptr && player != nullptr && gameObject == player)
	//{
	//	if (player->GetPassengerCount() >= requiredPassengerCount)
	//	{
	//		PauseTimer();
	//		
	//	}
	//}
}

std::string DriveObjective::Type()
{
	return "DriveObjective";
}