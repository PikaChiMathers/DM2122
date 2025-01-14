#include "Camera4.h"
#include "Application.h"
#include "Mtx44.h"

#define ZOOM_SPEED 70.f
#define CAMERA_SPEED 30.f


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
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera4::Update(double dt)
{
	view = (target - position).Normalized();
	right = view.Cross(up);
	yaw = ZOOM_SPEED * static_cast<float>(dt);
	pitch = ZOOM_SPEED * static_cast<float>(dt);

	if (Application::IsKeyPressed('W'))
	{
		Vector3 newPos = position + view * 0.3f * ZOOM_SPEED * dt;
		if (InBoundCheckShop(newPos) && InBoundCheckBus(newPos)) position = newPos;
	}
	else if (Application::IsKeyPressed('S'))
	{
		Vector3 newPos = position - view * 0.3f * ZOOM_SPEED * dt;
		if (InBoundCheckShop(newPos) && InBoundCheckBus(newPos)) position = newPos;
	}

	if (Application::IsKeyPressed('A'))
	{
		Vector3 newPos = position - right * 0.3f * CAMERA_SPEED * dt;
		if (InBoundCheckShop(newPos) && InBoundCheckBus(newPos)) position = newPos;
	}
	else if (Application::IsKeyPressed('D'))
	{
		Vector3 newPos = position + right * 0.3f * CAMERA_SPEED * dt;
		if (InBoundCheckShop(newPos) && InBoundCheckBus(newPos)) position = newPos;
	}

	position.y = defaultPosition.y;

	if (Application::IsKeyPressed('I'))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
	}
	if (Application::IsKeyPressed('K'))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-pitch, right.x, right.y, right.z);
		view = rotation * view * 0.3f;
	}
	if (Application::IsKeyPressed('J'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('L'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}

	target = position + view;

	if (Application::IsKeyPressed('R'))
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

bool Camera4::InBoundCheckShop(Vector3 pos)
{
	return (pos.x > shopLowerBound.x && pos.x < shopUpperBound.x && pos.y > shopLowerBound.y && pos.y < shopUpperBound.y && pos.z > shopLowerBound.z && pos.z < shopUpperBound.z);
}

bool Camera4::InBoundCheckBus(Vector3 pos)
{
	return !(pos.x > busLowerBound.x && pos.x < busUpperBound.x && pos.y > busLowerBound.y && pos.y < busUpperBound.y && pos.z > busLowerBound.z && pos.z < busUpperBound.z);
}

void Camera4::setShopBound(Vector3 botPosition, Vector3 topPosition)
{
	shopLowerBound = botPosition;
	shopUpperBound = topPosition;
}

void Camera4::setBusBound(Vector3 botPosition, Vector3 topPosition)
{
	busLowerBound = botPosition;
	busUpperBound = topPosition;
}