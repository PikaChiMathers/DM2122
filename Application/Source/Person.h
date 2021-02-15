#pragma once
#include "Vector3.h"

class Person
{
	enum PERSON_STATE
	{
		FACE_FRONT = 0,
		FACE_BACK,
		FACE_LEFT,
		FACE_RIGHT,
		STATIONARY,
	};

public:
	Person(Vector3 position);
	~Person();

	void Update(double dt);
	Vector3 getPosition();

private:
	Vector3 toMovePosition;		//position person is currently moving to
	Vector3 currentPosition;	//current position of person
	unsigned state;				//current state of person
	double waitTime;			//timer for stationary
};