#ifndef CAMERA_4_H
#define CAMERA_4_H

#include "Camera.h"

class Camera4 : public Camera
{
	int cameraMode; // 0 = azimuth, 1 = first person
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view, right;
	
	float yaw, pitch;

	double delay;

	Camera4();
	~Camera4();
	void CycleMode();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif