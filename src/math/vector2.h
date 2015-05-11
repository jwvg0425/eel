#pragma once
#include "base/macro.h"
#include "utility/Clonable.h"
#include <Windows.h>
#include <xnamath.h>

NS_EEL_BEGIN

//XMVECTOR series's proxy class.
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	explicit Vector2(XMFLOAT2 value);
	explicit Vector2(XMVECTOR value);

	operator XMFLOAT2();
	operator XMVECTOR();

	float		Dot(CXMVECTOR rhs);

	XMVECTOR	Cross(CXMVECTOR rhs);

	//data get
	float			GetX() const;
	float			GetY() const;
	ARRAY<float, 2>	GetArray() const;

	void			SetX(float x);
	void			SetY(float y);
	void			SetArray(ARRAY<float, 2> arr);

private:
	PROPERTY(XMFLOAT2, Value);
};

using Point2 = Vector2;

NS_EEL_END