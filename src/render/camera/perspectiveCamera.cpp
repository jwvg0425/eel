#include "perspectiveCamera.h"

USING_NS_EEL;

void eel::PerspectiveCamera::SetLens(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ)
{
	UpdateProjection(XMMatrixPerspectiveFovLH(fovAngle, aspect, nearZ, farZ));
}

eel::PerspectiveCamera::PerspectiveCamera(Point3 eyePos, Point3 targetPos, Vector3 up)
	:Camera(eyePos, targetPos, up)
{

}
