#pragma once
#ifndef BORDER_H
#define BORDER_H

#include"GameObject.h"

class Border : public GameObject
{
	double cooldown;
public:
	Border();
	~Border();
	void GameObjectUpdate(double dt);
	void OnTriggerStay(GameObject* gameObject);
	std::string Type();
};
#endif