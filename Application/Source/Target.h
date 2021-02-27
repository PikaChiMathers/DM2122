#ifndef CAMERA_TARGET
#define CAMERA_TARGET

#include "Camera.h"

class Target : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view, right;

	float yaw, pitch;

	float multiplier;

	//has_checked (to check whether the player has checked the building/target)
	//num_passengers (to store number of passengers in building)
	//progress (stores the percentage of progressthe player has made)
	bool has_checked;
	int num_passengers, progress;

	Target();
	~Target();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif