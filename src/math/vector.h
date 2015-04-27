#pragma once
#include "base/macro.h"
#include "utility/Clonable.h"
#include <Windows.h>
#include <xnamath.h>

NS_EEL_BEGIN

//XMVECTOR series's proxy class.
class Vector
{
public:
	Vector();
	Vector(float x, float y, float z, float w);
	Vector(XMFLOAT4 value);
	Vector(XMVECTOR value);

	operator XMFLOAT4();
	operator XMVECTOR();

	float		Dot(CXMVECTOR rhs);

	XMVECTOR	Cross(CXMVECTOR rhs);

	//data get
	float			GetX();
	float			GetY();
	float			GetZ();
	float			GetW();
	ARRAY<float, 4>	GetArray();

	void			SetX(float x);
	void			SetY(float y);
	void			SetZ(float z);
	void			SetW(float w);
	void			SetArray(ARRAY<float, 4> arr);

private:
	PROPERTY(XMFLOAT4, Value);
};

using Point = Vector;
using Color = Vector;

NS_EEL_END