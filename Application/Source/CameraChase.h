#ifndef CAMERACHASE_H
#define CAMERACHASE_H

#include "Camera.h"
#include "GameObject.h"

class CameraChase : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view, right;

	float yaw, pitch;

	float multiplier;

	GameObject* chase;

	float gap = 50, height = 100;

	CameraChase();
	~CameraChase();
	virtual void Init(GameObject* chase, const Vector3& up);
	virtual void Update(double dt);
	void SetChase(GameObject* chase);
};

#endif