#pragma once
#include "Vector3.h"

class Person
{
	enum PERSON_STATE
	{
		NOSTATE = 0,
		FACE_FRONT,
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
	int timesMoved;		//position person is currently moving to
	Vector3 currentPosition;	//current position of person
	unsigned state;				//current state of person
	double waitTime;			//timer for stationary
};