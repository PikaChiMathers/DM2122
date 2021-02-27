#include "Camera5.h"
#include "Application.h"
#include "Mtx44.h"

#define ZOOM_SPEED 80.f
#define CAMERA_SPEED 40.f

static const float rotational_speed = 45.0f;

Camera5::Camera5()
{
	multiplier = 1;
}

Camera5::~Camera5()
{
}

void Camera5::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
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
void Camera5::Update(double dt)
{
    view = (target - position).Normalized();
    right = view.Cross(up);
    yaw = ZOOM_SPEED * static_cast<float>(dt);
    pitch = ZOOM_SPEED * static_cast<float>(dt);

	if (Application::IsKeyPressed('S'))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(-pitch, right.x, right.y, right.z);
		view = rotation * view * 0.3f;
	}
	if (Application::IsKeyPressed('A'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(yaw * 0.6f, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('W'))
	{
		right.y = 0;
		right.Normalized();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
	}

	if (Application::IsKeyPressed('D'))
	{
		Mtx44 rotation;
		rotation.SetToRotation(-yaw * 0.6f, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
	}
	target = position + view;
}

void Camera5::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}
