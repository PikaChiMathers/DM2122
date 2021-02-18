#include"Bus.h"

Bus::Bus()
{
	acceleration = 10;
	brakePower = 1;
	AddCollider();
	GetCollider()->AddPhysics();
}

Bus::~Bus()
{
}