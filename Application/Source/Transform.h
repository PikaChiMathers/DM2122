#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#define RAD 3.1415926 / 180

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
	Vector3 up = Vector3(0, 1, 0);
	Vector3 right = Vector3(1, 0, 0);
	Vector3 foward = Vector3(0, 0, -1);
	void UpdateDirectionVectors()
	{
		//foward(cos(pitch)cos(yaw), cos(pitch)sin(yaw), sin(pitch))
		foward = Vector3(sin(-rotation.y * RAD), cos(rotation.y * RAD) * sin(rotation.x * RAD), -(cos(rotation.y * RAD) * cos(rotation.x * RAD)));
		right = foward.Cross(up);
	}
};

#endif