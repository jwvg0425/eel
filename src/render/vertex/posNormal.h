#pragma once
#include "base/macro.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct PosNormal
{
	PosNormal(Point3 pos, Vector3 normal)
		:m_Pos(pos), m_Normal(normal){}

	PosNormal(float x, float y, float z, float nx, float ny, float nz)
		:m_Pos(x, y, z), m_Normal(nx, ny, nz){}

	Point3 m_Pos;
	Vector3 m_Normal;
};

NS_EEL_END