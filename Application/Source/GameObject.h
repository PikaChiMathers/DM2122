#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<vector>
#include"Transform.h"
#include"ColliderManager.h"
class GameObject
{
	Transform transform;
	Collider* collider;
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
};

#endif