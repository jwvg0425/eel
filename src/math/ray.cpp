#include "ray.h"
#include <MathHelper.h>
#include "..\base\renderer.h"
#include "..\base\application.h"

eel::Ray::Ray()
	:m_RayOrigin(), m_RayDirection()
{
}

eel::Ray::Ray(const XMFLOAT3& origin, const XMFLOAT3& dir)
	: m_RayOrigin(Vector4 {origin.x, origin.y, origin.z, 1.f}),
	m_RayDirection(Vector4 {dir.x, dir.y, dir.z, 0.f})
{
}

eel::Ray::Ray(const XMFLOAT4& origin, const XMFLOAT4& dir)
	: m_RayOrigin(origin), m_RayDirection(dir)
{

}

eel::Ray::Ray(const Point3& origin, const Vector3& dir)
	: m_RayOrigin(Vector4 {origin.GetX(), origin.GetY(), origin.GetZ(), 1.f}),
	m_RayDirection(Vector4 {dir.GetX(), dir.GetY(), dir.GetZ(), 0.f})
{
}

eel::Ray::Ray(const Point4& origin, const Vector4& dir)
	: m_RayOrigin(origin), m_RayDirection(dir)
{
}

eel::Ray::Ray(int sx, int sy)
{
	auto camera = Renderer::GetInstance()->GetCurrentCamera();
	Matrix4 proj = camera->GetProjection();

	auto app = Application::GetInstance();
	float clientWidth = app->GetWidth();
	float clientHeight = app->GetHeight();
	
	float vx = ( +2.f*sx / clientWidth - 1.f ) / proj(0, 0);
	float vy = ( -2.f*sy / clientHeight + 1.f ) / proj(1, 1);

	Point4 originInViewCoordinate(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4 dirInViewCoordinate(vx, vy, 1.f, 0.f);

	Matrix4 view = camera->GetView();
	XMMATRIX viewInverse = XMMatrixInverse(&XMMatrixDeterminant(view), view);

	m_RayOrigin = XMVector3TransformCoord(originInViewCoordinate, viewInverse);
	m_RayDirection = XMVector3TransformCoord(dirInViewCoordinate, viewInverse);
}

	
