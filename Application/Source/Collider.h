#pragma once
#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vertex.h"

struct Size
{
	float x, y, z;
	Size(float x = 1, float y = 1, float z = 1) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

struct Collider
{
	Position position;
	Size size;
};

#endif