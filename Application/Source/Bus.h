#pragma once
#ifndef BUS_H
#define BUS_H

#include"GameObject.h"

class Bus : public GameObject
{
	float acceleration, brakePower;
	bool stop; // when we dont want the bus to move at all like if it is paused or smth
	float overSteerPct; // 0 - max oversteer (drifting), 1 - no oversteer
	enum ENUM_STATE
	{
		STATIC,
		MOVABLE,
		OUT_OF_CONTROL,
	};

public:
	Bus();
	~Bus();
	void setAccel(float accel);
	void setBrakePower(float brake);
	void setStop(bool stop);// when we dont want the bus to move at all like if it is paused or smth
	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif