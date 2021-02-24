#include "TriggerCollider.h"

TriggerCollider::TriggerCollider()
{
	SetScale(Scale(2, 2, 2));
	is_triggered = false;

	AddCollider();
	GetCollider()->SetIsTrigger(true);
}

TriggerCollider::~TriggerCollider()
{
}

bool TriggerCollider::IsTriggered()
{
	return is_triggered;
}

void TriggerCollider::OnTriggerStay(GameObject* gameObject)
{
	if (gameObject->Type() == "Goose")
	{
		if (Application::IsKeyPressed(VK_SPACE))
		{
			is_triggered = true;
		}
		else
			is_triggered = true;
	}
	else
		is_triggered = false;
}

