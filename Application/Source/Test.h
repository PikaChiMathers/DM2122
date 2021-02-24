#pragma once
#ifndef TEST_H
#define TEST_H

#include"GameObject.h"

class Test : public GameObject
{
public:
	Test();
	~Test();
	
	void GameObjectUpdate(double dt);
	void OnTriggerEnter(GameObject* gameObject);
	void OnTriggerStay(GameObject* gameObject);
	void OnTriggerExit(GameObject* gameObject);
	std::string Type();
};

#endif