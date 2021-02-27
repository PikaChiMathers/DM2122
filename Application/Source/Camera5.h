#ifndef CAMERA_5_H
#define CAMERA_5_H

#include "Camera.h"

class Camera5 : public Camera
{
public:

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view, right;

	float yaw, pitch;

	float multiplier;

	Camera5();
	~Camera5();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif