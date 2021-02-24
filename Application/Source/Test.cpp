#include"Test.h"

Test::Test()
{
	AddCollider();
	GetCollider()->SetIsTrigger(true);
}

Test::~Test()
{
}

void Test::GameObjectUpdate(double dt)
{
	
}

void Test::OnTriggerEnter(GameObject* gameObject)
{
	std::cout << "Enter: " << gameObject->Type() << std::endl;
}

void Test::OnTriggerStay(GameObject* gameObject)
{
	std::cout << "Stay: " << gameObject->Type() << std::endl;
}

void Test::OnTriggerExit(GameObject* gameObject)
{
	std::cout << "Exit: " << gameObject->Type() << std::endl;
}



std::string Test::Type()
{
	return "Test";
}