#pragma once
#ifndef MONEY_H
#define MONEY_H

#include "GameObject.h"
#include "Score.h"

class Money : public GameObject
{
private:
	int money;
	GameObject* coins;
	Score score;

public:
	Money();
	~Money();
	void IncreaseMoney(int);
	void SuccessfulTourist(int);
	void DecreaseMoney(int);
	void SetMoney(int);
	void ResetMoney();
	int getMoney();
	void OnTriggerEnter(GameObject*);
};
#endif
