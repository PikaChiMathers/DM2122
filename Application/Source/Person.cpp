#include "Person.h"

Person::Person(Vector3 position) : currentPosition(position)
{
	srand((unsigned)time(0));
	toMovePosition = currentPosition;
}

Person::~Person()
{

}

void Person::Update(double dt)
{
	if (currentPosition == toMovePosition && waitTime <= 0)
	{
		int result = rand() % 4;
		if (result == 0)
		{
			toMovePosition.x += 10;
			state = FACE_FRONT;
		}
		else if (result == 1)
		{
			toMovePosition.z += 10;
			state = FACE_LEFT;
		}
		else if (result == 2)
		{
			toMovePosition.z -= 10;
			state = FACE_RIGHT;
		}
		else if (result == 3)
		{
			waitTime = 3;
			state = STATIONARY;
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
	}
}

Vector3 Person::getPosition()
{
	return currentPosition;
}
