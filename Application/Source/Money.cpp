#include "Money.h"

Money::Money()
{
	money = 0;
}

void Money::IncreaseMoney(int add)
{
	add += money;
}

void Money::SuccessfulTourist(int num)
{
	IncreaseMoney(10 * num);
}

void Money::DecreaseMoney(int minus)
{
	minus -= money;
}

void Money::ResetMoney()
{
	money = 0;
}

int Money::getMoney()
{
	return money;
}
