//#pragma once
//#ifndef GAMEOBJECTMANAGER_H
//#define GAMEOBJECTMANAGER_H
//
//#include<vector>
//
//#include"GameObject.h"
//#include"Application.h"
//
//class GameObject;
//
//struct Collide
//{
//	GameObject* gameObject;
//	Vector3 axis;
//	float distance;
//	Collide()
//	{
//		gameObject = nullptr;
//		distance = -1;
//	}
//};
//
//class GameObjectManager // use this as the base class for objects
//{
//	std::vector<GameObject*>InTrigger;
//
//	// all GameObjects
//	std::vector<GameObject*>GameObjectList; 
//	// GameObjects with Colliders
//	std::vector<GameObject*>ColliderList;
//
//	/**
//	* Used for OBB collision detection.
//	* returns value of -1 if theres no overlap
//	*/
//	float SATcalculation(Vector3 axis, std::vector<Vector3>points1, std::vector<Vector3>points2);
//public:
//
//	bool ListContains(GameObject* col);
//	void PushCollider(GameObject* col);
//	void EraseCollider(GameObject* col);
//	//returns first gameobject found that is within a collider box
//	Collide CheckCollision(Collider* col);
//	Collide CheckCollision(Collider refCol, Collider* exclude = nullptr);
//	//return all gameobjects found within a collider box
//	std::vector<Collide> CheckCollisions(Collider* col);
//	std::vector<Collide> CheckCollisions(Collider refCol, Collider* exclude = nullptr);
//
//	// run every update in Scene::Update
//	void GameObjectUpdateManager(double dt); 
//};
//
//#endif