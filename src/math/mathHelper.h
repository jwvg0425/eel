#pragma once
#include "base/macro.h"
#include "math/matrix.h"

NS_EEL_BEGIN

namespace Math
{
	static const float PI = 3.141592f;

	Matrix4 inverseTranspose(Matrix4 mat);
};

NS_EEL_END