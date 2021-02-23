#pragma once
#ifndef BUS_H
#define BUS_H

#include"GameObject.h"

class Bus : public GameObject
{
	float acceleration, brakePower, grip;
public:
	Bus();
	~Bus();
	void setAccel(float accel);
	void setBrakePower(float brake);
	void setGrip(float grip);
	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif