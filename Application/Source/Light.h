#pragma once
#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	bool isOn = true;
	
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
		LIGHT_MULTIPLE,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;


	Light(float r = 1, float g = 1, float b = 1, float x = 0, float y = 0, float z = 0, float power = 0, float kC = 0, float kL = 0, float kQ = 0)
	{
		Set(r, g, b, x, y, z, power, kC, kL, kQ);
	}

	void Set(float r, float g, float b, float x, float y, float z, float power, float kC, float kL, float kQ)
	{
		color.Set(r, g, b);
		position.Set(x, y, z);
		this->power = power;
		this->kC = kC;
		this->kL = kL;
		this->kQ = kQ;
	}
	
	void colorSet(float r, float g, float b)
	{
		color.Set(r, g, b);
	}
};

