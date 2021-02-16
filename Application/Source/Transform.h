#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vertex.h"

struct Rotation
{
	float x, y, z;
	Rotation(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

struct Scale
{
	float x, y, z;
	Scale(float x = 1, float y = 1, float z = 1) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

struct Transform
{
	Position position;
	Rotation rotation;
	Scale scale;
	Vector3 up;
	Vector3 right;
	Vector3 foward;
	void Update()
	{
		
	}
};

#endif