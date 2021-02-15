#include "Person.h"

Person::Person(Vector3 position) : currentPosition(position), timesMoved(100), state(NOSTATE)
{
	srand((unsigned)time(0));
}

Person::~Person()
{

}

void Person::Update(double dt)
{
	if (timesMoved == 100 && waitTime <= 0)
	{
		switch (rand() % 4)
		{
		case 0:
			state = FACE_FRONT;
			timesMoved = 0;
			break;
		case 1:
			state = FACE_LEFT;
			timesMoved = 0;
			break;
		case 2:
			state = FACE_RIGHT;
			timesMoved = 0;
			break;
		case 3:
			state = STATIONARY;
			waitTime = 2;
			break;
		default:
			break;
		}
	}
	else if (waitTime > 0)
		waitTime -= dt;
	else
	{
		if (state == FACE_FRONT)
			currentPosition.x += 0.1;
		else if (state == FACE_LEFT)
			currentPosition.z += 0.1;
		else if (state == FACE_RIGHT)
			currentPosition.z -= 0.1;

		++timesMoved;
	}
}

Vector3 Person::getPosition()
{
	return currentPosition;
}
