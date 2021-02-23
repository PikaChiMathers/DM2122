#include"Objects.h"

Objects::Objects()
{
	AddCollider();
	AddPhysics();
}

Objects::~Objects()
{
}

void Objects::GameObjectUpdate(double dt)
{
}

std::string Objects::Type()
{
	return "Objects";
}