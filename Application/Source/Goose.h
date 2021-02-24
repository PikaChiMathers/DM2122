#pragma once
#ifndef GOOSE_H
#define GOOSE_H

#include"GameObject.h"

class Goose : public GameObject
{
	float acceleration;
public:
	Goose();
	~Goose();
	void GameObjectUpdate(double dt);
	std::string Type();
};
#endif