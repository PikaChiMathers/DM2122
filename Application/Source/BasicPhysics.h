#pragma once
#ifndef BASICPHYSICS_H
#define BASICPHYSICS_H

#include "Vector3.h"

class BasicPhysics
{
	Vector3 velocity;
	float mass, drag;
	bool usesGravity;
public:
	BasicPhysics(float mass = 1.f, float drag = 0.f);
	~BasicPhysics();
	void SetGravity(bool use);
	bool UsesGravity();
	void SetMass(int mass);
	int GetMass();
	void SetDrag(int drag);
	int GetDrag();
	void SetVelocity(Vector3 velocity);
	void AddVelocity(Vector3 velocity);
	Vector3 GetVelocity();
	void PhysicsUpdate(double dt); // call in Update in GameObject class
};
#endif