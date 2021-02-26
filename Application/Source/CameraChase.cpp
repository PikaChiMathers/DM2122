#include "CameraChase.h"
#include "Application.h"
#include "Mtx44.h"

#define ZOOM_SPEED 80.f
#define CAMERA_SPEED 40.f

static const float rotational_speed = 45.0f;

CameraChase::CameraChase()
{
	multiplier = 1;
}

CameraChase::~CameraChase()
{
}

void CameraChase::Init(GameObject* chase, const Vector3& up)
{
    this->position = defaultPosition = chase == nullptr ? Vector3(5, 5, 0) : (Vector3(chase->GetPositionX(), chase->GetPositionY(), chase->GetPositionZ()) + chase->GetFoward() * -gap + chase->GetUp() * height);
    this->target = defaultTarget = chase == nullptr ? Vector3(0, 0, 0) : Vector3(chase->GetPositionX(), chase->GetPositionY(), chase->GetPositionZ());
    view = (target - position).Normalized();
    right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

//1st person
void CameraChase::Update(double dt)
{
    //yaw = ZOOM_SPEED * static_cast<float>(dt);
    //pitch = ZOOM_SPEED * static_cast<float>(dt);

    position = chase == nullptr ? Vector3(5, 5, 0) : (Vector3(chase->GetPositionX(), chase->GetPositionY(), chase->GetPositionZ()) + chase->GetFoward() * -gap + chase->GetUp() * height);
    target = chase == nullptr ? Vector3(0, 0, 0) : Vector3(chase->GetPositionX(), chase->GetPositionY(), chase->GetPositionZ());

    view = (target - position).Normalized();
    right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    up = right.Cross(view).Normalized();
}

void CameraChase::SetChase(GameObject* chase)
{
    this->chase = chase;
}
