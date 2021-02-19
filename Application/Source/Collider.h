#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vertex.h"
#include "Transform.h"
#include <vector>

struct Size
{
	float x, y, z;
	Size(float x = 1, float y = 1, float z = 1)
	{
		Set(x, y, z);
	}
	void Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
class Collider
{
	Position position;
	Rotation rotation;
	Size size;
	bool isTrigger; // allows objects to pass thru

public:
	Collider();
	Collider(Position position, Size size);
	~Collider();
	void SetPosition(Position pos);
	void SetRotation(Rotation rot);
	void SetSize(Size size);
	Position GetPosition();
	Rotation GetRotation();
	Size GetSize();
	void SetIsTrigger(bool isTrigger);
	bool GetIsTrigger();
};
#endif