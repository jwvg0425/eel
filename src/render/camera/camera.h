#pragma once
#include "base/object.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "math/ray.h"

NS_EEL_BEGIN

class Camera : public Object
{
public:
	Camera(Point3 eyePos, Point3 targetPos, Vector3 up);
	virtual ~Camera() = default;

	Matrix4 GetViewProjection() const;

	//first two parameter means (width, height) in orthographic camera and (fovAngleY, aspect) in perspective camera
	virtual void SetLens(FLOAT angleOrWidth, FLOAT aspectOrHeight, FLOAT nearZ, FLOAT farZ) = 0;

	void Walk(float d);
	void Strafe(float d);
	void Pitch(float angle);
	void RotateY(float angle);


	void SetEyePos(Point3 eyePos);
	void SetUpVector(Vector3 up);
	Ray	GetCameraRay() const
	{
		return Ray(m_EyePos, m_Look);
	}

protected:
	void UpdateView();
	void UpdateProjection(Matrix4 matrix);
	
private:
	READ_ONLY(Vector3, Up);
	READ_ONLY(Vector3, Right);

	READ_ONLY(Point3, EyePos);
	READ_ONLY(Vector3, Look);
	READ_ONLY(Matrix4, View);
	READ_ONLY(Matrix4, Projection);
};

NS_EEL_END