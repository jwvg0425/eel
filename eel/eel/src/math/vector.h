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

	float	Dot(CXMVECTOR rhs);

private:
	XMFLOAT4 m_Value;
};

NS_EEL_END