#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 10.f;

	if(Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Mtx44 left;
		left.SetToRotation(90, 0, 1, 0);
		position += left * view * ZOOM_SPEED * static_cast<float>(dt);
		position.y = 2;
		target = position + view;
	}
	else if(Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Mtx44 right;
		right.SetToRotation(-90, 0, 1, 0);
		position += right * view * ZOOM_SPEED * static_cast<float>(dt);
		position.y = 2;
		target = position + view;
	}
	if(Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		position += view * ZOOM_SPEED * static_cast<float>(dt);
		position.y = 2;
		target = position + view;
	}
	else if(Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * ZOOM_SPEED * static_cast<float>(dt);
		position.y = 2;
		target = position + view;
	}

	if (Application::IsKeyPressed('J'))
	{
		float yaw = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	else if (Application::IsKeyPressed('L'))
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('I'))
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	else if (Application::IsKeyPressed('K'))
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}