#pragma once
#ifndef TRIGGER_COLLIDER
#define TRIGGER_COLLIDER
#include "GameObject.h"

class TriggerCollider : public GameObject
{
private:
	bool is_triggered;
public:
	TriggerCollider();
	~TriggerCollider();
	bool IsTriggered();
	void OnTriggerStay(GameObject* gameObject);
};
#endif