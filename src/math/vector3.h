#pragma once
#include "base/macro.h"
#include "utility/Clonable.h"
#include <Windows.h>
#include <xnamath.h>

NS_EEL_BEGIN

//XMVECTOR series's proxy class.
class Vector3
{
public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(const XMFLOAT3& value);
	Vector3(const XMVECTOR& value);

	Vector3(const Vector3& rhs) = default;

	operator XMFLOAT3() const;
	operator XMVECTOR() const;

	float		Dot(CXMVECTOR rhs);

	XMVECTOR	Cross(CXMVECTOR rhs);

	XMVECTOR	Normalize();
	XMVECTOR	MultiplyAdd(XMVECTOR v1, XMVECTOR v2);
	XMVECTOR	Transform(XMMATRIX& matrix);
	XMVECTOR	TransformNormal(XMMATRIX& matrix);

	//data get
	float			GetX() const;
	float			GetY() const;
	float			GetZ() const;
	ARRAY<float, 3>	GetArray() const;

	void			SetX(float x);
	void			SetY(float y);
	void			SetZ(float z);
	void			SetArray(ARRAY<float, 3> arr);

private:
	PROPERTY(XMFLOAT3, Value);
};

using Point3 = Vector3;
using Color3 = Vector3;

NS_EEL_END