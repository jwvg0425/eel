#pragma once
#include "math/vector.h"

NS_EEL_BEGIN

class Ray
{
public:
	Ray();
	Ray(const XMFLOAT3& origin, const XMFLOAT3& dir);
	Ray(const XMFLOAT4& origin, const XMFLOAT4& dir);
	Ray(const Point3& origin, const Vector3& dir);
	Ray(const Point4& origin, const Vector4& dir);

	Ray(const Ray&) = default;
	//Init with viewport coordinate
	Ray(int sx, int sy);

private:
	PROPERTY(Point4, RayOrigin);
	PROPERTY(Vector4, RayDirection);
};

NS_EEL_END
