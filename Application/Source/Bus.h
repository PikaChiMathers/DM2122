#pragma once
#ifndef BUS_H
#define BUS_H

#include"GameObject.h"

class Bus : public GameObject
{
	float acceleration, brakePower;
public:
	Bus();
	~Bus();
	void moveFoward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void setAccel(float accel);
	void setBrakePower(float brake);
};
#endif