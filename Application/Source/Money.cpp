#include "Money.h"

Money::Money()
{
	player = nullptr;
	//money = 0;

	value = 50;
	AddCollider();
	GetCollider()->SetIsTrigger(true);
}

Money::~Money()
{
	//Nothing.
}

void Money::SetPlayer(Bus* player)
{
	this->player = player;
}

void Money::SetValue(int value)
{
	this->value = value;
}

void Money::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject == player && player != nullptr)
	{
		player->AddMoney(value);
		//Coin collected sound
		Delete();
	}
	//IncreaseMoney(15);
	//score.setScore(0, getMoney());
}
//
//void Money::IncreaseMoney(int add)
//{
//	money += add;
//}
//
//void Money::SuccessfulTourist(int num)
//{
//	IncreaseMoney(10 * num);
//}
//
//void Money::DecreaseMoney(int minus)
//{
//	money -= minus;
//}
//
//void Money::SetMoney(int value)
//{
//	money = value;
//}
//
//void Money::ResetMoney()
//{
//	money = 0;
//}
//
//int Money::getMoney()
//{
//	return money;
//}

std::string Money::Type()
{
	return "Money";
}
