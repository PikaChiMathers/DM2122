#include "Money.h"

Money::Money()
{
	money = 0;
	AddCollider();
	SetPosition(Position(5, 0, 0));
	GetCollider()->SetIsTrigger(true);
}

Money::~Money()
{
	//Nothing.
}

void Money::OnTriggerEnter(GameObject*)
{
	//Coin collected sound
	IncreaseMoney(15);
	score.setScore(0, getMoney());
	delete this;
}

void Money::IncreaseMoney(int add)
{
	money += add;
}

void Money::SuccessfulTourist(int num)
{
	IncreaseMoney(10 * num);
}

void Money::DecreaseMoney(int minus)
{
	money -= minus;
}

void Money::SetMoney(int value)
{
	money = value;
}

void Money::ResetMoney()
{
	money = 0;
}

int Money::getMoney()
{
	return money;
}
