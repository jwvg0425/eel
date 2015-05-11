#pragma once
#include "math/matrix3.h"
#include "math/matrix4.h"

namespace Matrix
{
	XMMATRIX RotationAxis(XMVECTOR axis, float angle);
	XMMATRIX RotationX(float angle);
	XMMATRIX RotationY(float angle);
	XMMATRIX RotationZ(float angle);
};