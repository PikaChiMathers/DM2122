#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<vector>
#include"Transform.h"
#include"Collider.h"
#include"Application.h"
class GameObject // use this as the base class for objects that needs collider.
{
	Transform transform;
	Collider* collider; // add this for collider. from collider, you can add physics component.
public:
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

	virtual void GameObjectUpdate(double dt); // this runs every update in the Scene's update function.

private:
	static std::vector<GameObject*>GameObjectList; // all GameObjects
	static std::vector<GameObject*>ColliderList; // GameObjects with Colliders
public:
	static bool ListContains(GameObject* col);
	static void PushCollider(GameObject* col);
	static void EraseCollider(GameObject* col);
	static GameObject* CheckCollision(Collider* col);
	static GameObject* CheckCollision(Position pos, Size size = 1, Collider* exclude = nullptr);

	static void GameObjectUpdateManager(double dt); // run every update
};

#endif