#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

#define ZOOM_SPEED 80.f
#define CAMERA_SPEED 40.f

static const float rotational_speed = 45.0f;

Camera3::Camera3()
{
	multiplier = 1;
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    view = (target - position).Normalized();
    right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

//1st person
void Camera3::Update(double dt)
{
    view = (target - position).Normalized();
    right = view.Cross(up);
    yaw = ZOOM_SPEED * static_cast<float>(dt);
    pitch = ZOOM_SPEED * static_cast<float>(dt);

	if (Application::IsKeyPressed(SHIFT_PRESSED))
	{
		multiplier = 8;
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}
	}
	else multiplier = 1;
	if (Application::IsKeyPressed('Q'))
	{
		position += up * CAMERA_SPEED * multiplier * dt;
	}
	if (Application::IsKeyPressed('E'))
	{
		position -= up * CAMERA_SPEED * multiplier * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		position -= right * 0.3f * CAMERA_SPEED * multiplier * dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		position += right * 0.3f * CAMERA_SPEED * multiplier * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		position -= view * 0.3f * ZOOM_SPEED * multiplier * dt;
	}
	if (Application::IsKeyPressed('W'))
	{
		position += view * 0.3f * ZOOM_SPEED * multiplier * dt;
	}

	if (Application::IsKeyPressed(VK_DOWN))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-pitch, right.x, right.y, right.z);
		view = rotation * view * 0.3f;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
	}

	if (Application::IsKeyPressed(VK_RIGHT))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}
	target = position + view;
}

void Camera3::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}
