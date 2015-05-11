#pragma once
#include "base/macro.h"
#include "utility/Clonable.h"
#include <Windows.h>
#include <xnamath.h>

NS_EEL_BEGIN

//XMVECTOR series's proxy class.
class Vector4
{
public:
	Vector4();
	Vector4(float value);
	Vector4(float x, float y, float z, float w);
	Vector4(const XMFLOAT4& value);
	Vector4(const XMVECTOR& value);

	Vector4(const Vector4& rhs) = default;

	operator XMFLOAT4();
	operator XMVECTOR();

	float		Dot(CXMVECTOR rhs);

	XMVECTOR	Cross(CXMVECTOR rhs);

	XMVECTOR	Normalize();
	XMVECTOR	MultiplyAdd(XMVECTOR v1, XMVECTOR v2);
	XMVECTOR	Transform(XMMATRIX& matrix);

	//data get
	float			GetX() const;
	float			GetY() const;
	float			GetZ() const;
	float			GetW() const;
	ARRAY<float, 4>	GetArray() const;

	void			SetX(float x);
	void			SetY(float y);
	void			SetZ(float z);
	void			SetW(float w);
	void			SetArray(ARRAY<float, 4> arr);

private:
	PROPERTY(XMFLOAT4, Value);
};

using Point4 = Vector4;
using Color4 = Vector4;

NS_EEL_END