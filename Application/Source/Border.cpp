#include"Border.h"

Border::Border()
{
	cooldown = 0;
	AddCollider();
	GetCollider()->SetIsTrigger(true);
	SetScale(Scale(40, 40, 40));
}

Border::~Border()
{
}

void Border::GameObjectUpdate(double dt)
{
	if (cooldown > 0)
	{
		SetTag("Render");
		cooldown -= dt;
	}
	else
	{
		SetTag("");
		cooldown = 0;
	}
}

void Border::OnTriggerStay(GameObject* gameObject)
{
	if (gameObject != nullptr && gameObject->Type() == "Bus")
	{
		cooldown = 1;
	}
}

std::string Border::Type()
{
	return "Border";
}