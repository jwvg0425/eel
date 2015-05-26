#pragma once
#include "render/vertex/vertexUtil.h"

NS_EEL_BEGIN

struct PosBasic
{
	PosBasic()
		:m_Pos(0.0f, 0.0f, 0.0f), m_Normal(0.0f, 0.0f, 0.0f), m_Tex(0.0f, 0.0f){}

	PosBasic(Point3 pos, Vector3 normal, Point2 tex)
		:m_Pos(pos), m_Normal(normal), m_Tex(tex){}

	PosBasic(float x, float y, float z, float nx, float ny, float nz, float tx, float ty)
		:m_Pos(x, y, z), m_Normal(nx, ny, nz), m_Tex(tx, ty){}

	Point3 m_Pos;
	Vector3 m_Normal;
	Point2 m_Tex;
};


NS_EEL_END