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

struct OBB
{
	std::vector<Vector3>Points;
	std::vector<Vector3>Axes;
};

class Collider
{
	Size size;
	Transform transform;
	bool isTrigger; // allows objects to pass thru. use OnTriggerEnter, Stay or exit (from gameobject class) to get gameobjects inside.
public:
	Collider();
	~Collider();
	void SetPosition(Position pos);
	void SetRotation(Rotation rot);
	void SetTransform(Transform transform);
	void SetSize(Size size);
	Position GetPosition();
	Rotation GetRotation();
	Transform GetTransform();
	Size GetSize();
	void SetIsTrigger(bool isTrigger);
	bool GetIsTrigger();
	OBB GetOBBData();
};
#endif