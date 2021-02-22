#pragma once
#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H
#include"Collider.h"

class BoxCollider : public Collider
{
	std::vector<Vector3>points;
public:
	BoxCollider();
	~BoxCollider();
};
#endif