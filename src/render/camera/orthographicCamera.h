#pragma once
#include "render/camera/camera.h"

NS_EEL_BEGIN

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(Point3 eyePos, Point3 targetPos, Vector3 up);

	CREATE_FUNC(OrthographicCamera);

	virtual void SetLens(FLOAT width, FLOAT height, FLOAT nearZ, FLOAT farZ);
};

NS_EEL_END