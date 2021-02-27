#pragma once
#ifndef MONEY_H
#define MONEY_H

#include "GameObject.h"
#include "Bus.h"
#include "Score.h"

class Money : public GameObject
{
	//int money;
	int value;
	Score score;

	Bus* player;
public:
	Money();
	~Money();
	void SetPlayer(Bus* player);
	void SetValue(int value);
	/*void IncreaseMoney(int);
	void SuccessfulTourist(int);
	void DecreaseMoney(int);
	void SetMoney(int);
	void ResetMoney();
	int getMoney();*/

	void OnTriggerEnter(GameObject* gameObject);
	std::string Type();
};
#endif
