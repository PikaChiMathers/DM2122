#ifndef CAMERA_4_H
#define CAMERA_4_H

#include "Camera.h"

class Camera4 : public Camera
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

	Vector3 lowerBound;
	Vector3 upperBound;

	Camera4();
	~Camera4();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	bool InBoundCheck(Vector3 pos);
	virtual void Reset();

	void setBound(Vector3 botPosition, Vector3 topPosition);
};

#endif