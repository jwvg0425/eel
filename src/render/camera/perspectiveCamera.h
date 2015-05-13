#pragma once
#include "render/camera/camera.h"
#include "utility/makeCreate.h"

NS_EEL_BEGIN

class PerspectiveCamera : public Camera, public MakeCreate<PerspectiveCamera>
{
public:
	PerspectiveCamera(Point3 eyePos, Point3 targetPos, Vector3 up);

	virtual void SetLens(FLOAT fovAngle, FLOAT aspect, FLOAT nearZ, FLOAT farZ);
};

NS_EEL_END