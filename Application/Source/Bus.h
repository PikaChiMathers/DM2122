#pragma once
#ifndef BUS_H
#define BUS_H

#include"GameObject.h"

class Bus : public GameObject
{
	static int money;

	int moneyCurrent;
	float acceleration, brakePower;
	bool stop; // when we dont want the bus to move at all like if it is paused or smth
	float overSteerPct; // 0 - max oversteer (drifting), 1 - no oversteer
	int passengers;
	/*enum ENUM_STATE
	{
		STATIC,
		MOVABLE,
		OUT_OF_CONTROL,
	};*/
public:
	Bus();
	~Bus();
	void SetMoney(int amount);
	void AddMoney(int amount);
	int GetMoney();
	// set the number of passengers collected
	void SetPassengerCount(int count);
	//add 1 to the number of passengers collected
	void AddPassengerCount();
	//get the number of passengers collecetd
	int GetPassengerCount();
	void SetAccel(float accel);
	void SetBrakePower(float brake);
	void SetStop(bool stop);// when we dont want the bus to move at all like if it is paused or smth
	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif