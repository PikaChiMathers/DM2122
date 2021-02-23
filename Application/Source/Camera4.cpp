#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

Camera4::Camera4()
{
}

Camera4::~Camera4()
{
}

void Camera4::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera4::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;
	if(Application::IsKeyPressed('W'))
	{
		position.x += 1;
		if (position.x > upperBound.x)
			position.x = upperBound.x;
	}
	else if(Application::IsKeyPressed('S'))
	{
		position.x -= 1;
		if (position.x < lowerBound.x)
			position.x = lowerBound.x;
	}
	if(Application::IsKeyPressed('A'))
	{
		position.z += 1;
		if (position.z > upperBound.z)
			position.z = upperBound.z;
	}
	else if(Application::IsKeyPressed('D'))
	{
		position.z -= 1;
		if (position.z < upperBound.z)
			position.z = upperBound.z;
	}
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera4::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void Camera4::setBound(Vector3 botPosition, Vector3 topPosition)
{
	lowerBound = botPosition;
	upperBound = topPosition;
}