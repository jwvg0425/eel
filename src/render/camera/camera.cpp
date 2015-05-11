#include "camera.h"

USING_NS_EEL;

eel::Camera::Camera(Point3 eyePos, Point3 targetPos, Vector3 up)
	:m_EyePos(eyePos), m_Up(up)
{

}

eel::Matrix4 eel::Camera::GetViewProjection() const
{

}

void eel::Camera::Walk(float d)
{

}

void eel::Camera::Strafe(float d)
{

}

void eel::Camera::Pitch(float angle)
{

}

void eel::Camera::RotateY(float angle)
{

}

void eel::Camera::SetEyePos(Point3 eyePos)
{

}

void eel::Camera::SetUpVector(Vector3 up)
{

}
