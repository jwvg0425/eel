#pragma once
#include "base/object.h"
#include "math/vector.h"
#include "math/matrix.h"

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

	GETTER(Point3, m_EyePos, EyePos);
	void SetEyePos(Point3 eyePos);
	
	void SetUpVector(Vector3 up);

protected:
	void UpdateView();
	void UpdateProjection(Matrix4 matrix);
	
private:
	Point3 m_EyePos;
	Vector3 m_Up;
	Vector3 m_Right;

	READ_ONLY(Vector3, Look);
	READ_ONLY(Matrix4, View);
	READ_ONLY(Matrix4, Projection);
};

NS_EEL_END