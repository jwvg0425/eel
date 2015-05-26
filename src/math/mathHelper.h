#pragma once
#include <Windows.h>
#include <XNAMath.h>
#include "base/macro.h"
#include "math/matrix.h"

NS_EEL_BEGIN

namespace Math
{
	static const float PI = 3.141592f;
	static const float INF = FLT_MAX;
	extern const Matrix4 I;

	Matrix4 InverseTranspose(Matrix4 mat);
	
	BOOL IntersectRayTriangle(FXMVECTOR Origin, FXMVECTOR Direction, FXMVECTOR V0, CXMVECTOR V1, CXMVECTOR V2,
		FLOAT* pDist);

	XMMATRIX Inverse(Matrix4 mat);
};

NS_EEL_END