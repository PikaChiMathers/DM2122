#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<vector>
#include"Transform.h"
#include"Collider.h"
#include"BasicPhysics.h"
#include"Application.h"
class GameObject // use this as the base class for objects
{
	Transform transform;
	Collider* collider; // add this for collider. from collider, you can add physics component.
	BasicPhysics* physics; // add this if you want the object to stop moving when colliding with other colliders. Use the add/set velocity function to move
	std::string tag;

public:
	//Used to store GameObjects that are inside a trigger box of the current GameObject.
	std::vector<GameObject*>InTrigger;

	GameObject();
	~GameObject();
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);
	void SetPosition(Position pos);
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	Position GetPosition();
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void SetRotate(Rotation rot);
	float GetRotateX();
	float GetRotateY();
	float GetRotateZ();
	Rotation GetRotate();
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);
	void SetScale(Scale scale);
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();
	Scale GetScale();

	void AddCollider();
	void RemoveCollider();
	Collider* GetCollider();
	void ColliderUpdate();

	void AddPhysics();
	BasicPhysics* GetPhysics();
	void RemovePhysics();

	void SetTag(std::string tag);
	std::string GetTag();

	// this runs every update in the Scene's update function.
	virtual void GameObjectUpdate(double dt); 

	// return the name of the class
	virtual std::string Type(); 

	//Return GameObject that entered the trigger collision box and runs the function
	virtual void OnTriggerEnter(GameObject* gameObject);
	//Return GameObject that has already entered the trigger collision box and is still inside, and runs the function
	virtual void OnTriggerStay(GameObject* gameObject);
	//Return GameObject that exits the trigger collision box and runs the function
	virtual void OnTriggerExit(GameObject* gameObject);

private:
	// all GameObjects
	static std::vector<GameObject*>GameObjectList; 
	// GameObjects with Colliders
	static std::vector<GameObject*>ColliderList;
public:
	static bool ListContains(GameObject* col);
	static void PushCollider(GameObject* col);
	static void EraseCollider(GameObject* col);
	//returns first gameobject found that is within a collider box
	static GameObject* CheckCollision(Collider* col);
	static GameObject* CheckCollision(Position pos, Size size = 1, Collider* exclude = nullptr);
	//return all gameobjects found within a collider box
	static std::vector<GameObject*> CheckCollisions(Collider* col);
	static std::vector<GameObject*> CheckCollisions(Position pos, Size size = 1, Collider* exclude = nullptr);

	// run every update in Scene::Update
	static void GameObjectUpdateManager(double dt); 
};

#endif