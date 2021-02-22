#pragma once
#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "GameObject.h"

class Collectibles : public GameObject
{
private:
	int data;

public:
	Collectibles();

	void tookCollectible(bool);
	int getCollectbleAmt();

};
#endif
