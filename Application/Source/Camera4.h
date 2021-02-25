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

	Vector3 shopLowerBound;
	Vector3 shopUpperBound;
	Vector3 busLowerBound;
	Vector3 busUpperBound;

	Camera4();
	~Camera4();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();

	bool InBoundCheckShop(Vector3 pos);
	bool InBoundCheckBus(Vector3 pos);
	void setShopBound(Vector3 botPosition, Vector3 topPosition);
	void setBusBound(Vector3 botPosition, Vector3 topPosition);
};

#endif