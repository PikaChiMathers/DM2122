#pragma once
class Money
{
private:
	int money;

public:
	Money();
	void IncreaseMoney(int);
	void SuccessfulTourist(int);
	void DecreaseMoney(int);
	void SetMoney(int);
	void ResetMoney();
	int getMoney();
};

