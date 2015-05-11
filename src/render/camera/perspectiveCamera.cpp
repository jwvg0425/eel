#include "perspectiveCamera.h"
#include "base/application.h"

USING_NS_EEL;

void eel::PerspectiveCamera::SetLens(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ)
{
	UpdateProjection(XMMatrixPerspectiveFovLH(fovAngle, aspect, nearZ, farZ));
}

eel::PerspectiveCamera::PerspectiveCamera(Point3 eyePos, Point3 targetPos, Vector3 up)
	:Camera(eyePos, targetPos, up)
{
	SetLens(0.25f, Application::GetInstance()->GetAspectRatio(), 1.0f, 1000.0f);
}
