#pragma once
#include "Vector3.h"
#include "GameObject.h"
#include "Bus.h"

class Person : public GameObject
{
//	enum PERSON_STATE
//	{
//		NOSTATE = 0,
//		FACE_FRONT,
//		FACE_LEFT,
//		FACE_RIGHT,
//		STATIONARY,
//	};
//
	Bus* player;
public:
	//Person(Vector3 position);
	Person();
	~Person();
	void SetPlayer(Bus* player);

	void GameObjectUpdate(double dt);
	void OnTriggerEnter(GameObject* gameObject);

	std::string Type();
//	void Update(double dt);		//moves person per update
//	Vector3 getPosition();		//return position of person
//
//private:
//	Vector3 currentPosition;	//current position of person
//	int timesMoved;				//position person is currently moving to
//	unsigned state;				//current state of person
//	double waitTime;			//timer for stationary
};