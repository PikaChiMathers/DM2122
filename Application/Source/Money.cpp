#include "Money.h"

Money::Money()
{
	money = 0;
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
