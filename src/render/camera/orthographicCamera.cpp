#include "orthographicCamera.h"

USING_NS_EEL;

void eel::OrthographicCamera::SetLens(FLOAT width, FLOAT height, FLOAT nearZ, FLOAT farZ)
{
	UpdateProjection(XMMatrixOrthographicLH(width, height, nearZ, farZ));
}

eel::OrthographicCamera::OrthographicCamera(Point3 eyePos, Point3 targetPos, Vector3 up)
	:Camera(eyePos, targetPos, up)
{

}
