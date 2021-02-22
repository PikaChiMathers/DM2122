#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include"Collider.h"

class BoxCollider : public Collider
{
public:
	BoxCollider();
	~BoxCollider();
	OBB GetOBBData();
};
#endif