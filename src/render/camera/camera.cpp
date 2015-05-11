#include "camera.h"

USING_NS_EEL;

eel::Camera::Camera(Point3 eyePos, Point3 targetPos, Vector3 up)
	:m_EyePos(eyePos)
{
	Vector3 L = Vector3(targetPos - eyePos).Normalize();
	Vector3 R = up.Cross(L);
	Vector3 U = L.Cross(R);

	m_Look = L;
	m_Up = U;
	m_Right = R;

	UpdateView();
}

eel::Matrix4 eel::Camera::GetViewProjection() const
{
	return m_View*m_Projection;
}

void eel::Camera::Walk(float d)
{
	Vector3 s = Vector3(d);

	m_EyePos = s.MultiplyAdd(m_Look, m_EyePos);

	UpdateView();
}

void eel::Camera::Strafe(float d)
{
	Vector3 s = Vector3(d);

	m_EyePos = s.MultiplyAdd(m_Right, m_EyePos);

	UpdateView();
}

void eel::Camera::Pitch(float angle)
{
	XMMATRIX r = Matrix::RotationAxis(m_Right, angle);

	m_Up = m_Up.TransformNormal(r);
	m_Look = m_Look.TransformNormal(r);
}

void eel::Camera::RotateY(float angle)
{
	XMMATRIX r = Matrix::RotationY(angle);

	m_Right = m_Right.TransformNormal(r);
	m_Up = m_Up.TransformNormal(r);
	m_Look = m_Look.TransformNormal(r);
}

void eel::Camera::SetEyePos(Point3 eyePos)
{
	m_EyePos = eyePos;
	
	UpdateView();
}

void eel::Camera::SetUpVector(Vector3 up)
{
	m_Up = up;

	UpdateView();
}

void eel::Camera::UpdateView()
{
	m_Look = m_Look.Normalize();
	m_Up = Vector3(m_Look.Cross(m_Right)).Normalize();
	m_Right = m_Up.Cross(m_Look);

	float x = -m_EyePos.Dot(m_Right);
	float y = -m_EyePos.Dot(m_Up);
	float z = -m_EyePos.Dot(m_Look);

	m_View(0, 0) = m_Right.GetX();
	m_View(1, 0) = m_Right.GetY();
	m_View(2, 0) = m_Right.GetZ();
	m_View(3, 0) = x;

	m_View(0, 1) = m_Up.GetX();
	m_View(1, 1) = m_Up.GetY();
	m_View(2, 1) = m_Up.GetZ();
	m_View(3, 1) = y;

	m_View(0, 2) = m_Look.GetX();
	m_View(1, 2) = m_Look.GetY();
	m_View(2, 2) = m_Look.GetZ();
	m_View(3, 2) = z;

	m_View(0, 3) = 0.0f;
	m_View(1, 3) = 0.0f;
	m_View(2, 3) = 0.0f;
	m_View(3, 3) = 1.0f;
}

void eel::Camera::UpdateProjection(Matrix4 matrix)
{
	m_Projection = matrix;
}
