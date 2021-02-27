#pragma once
#ifndef DRIVEOBJECTIVE_H
#define DRIVEOBJECTIVE_H

#include"GameObject.h"
#include"Bus.h"

class DriveObjective : public GameObject
{
	int requiredPassengerCount;
	bool pause;
	double timer;
	Bus* player;
public:
	DriveObjective();
	~DriveObjective();
	//reference the player object
	void SetPlayer(Bus* player);
	//set the min no. of passengers to collect
	void SetReqiuredPassengerCount(int count);
	//set the time limit
	void SetTimer(double timer);
	//start the time
	void StartTimer();
	//pause the time
	void PauseTimer();
	//get the remaining time
	double GetTime();
	void GameObjectUpdate(double dt);
	void OnTriggerStay(GameObject* gameObject);
	std::string Type();
};
#endif