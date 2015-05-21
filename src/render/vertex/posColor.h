#pragma once
#include "render/vertex/vertexUtil.h"

NS_EEL_BEGIN

struct PosColor
{
	PosColor()
		:m_Pos(0.0f, 0.0f, 0.0f), m_Color(0.0f, 0.0f, 0.0f, 0.0f){}

	PosColor(Point3 pos, Color4 color)
		:m_Pos(pos), m_Color(color) {}

	PosColor(float x, float y, float z, float r, float g, float b, float a)
		:m_Pos(x, y, z), m_Color(r, g, b, a){}

	PosColor(float x, float y, float z, Color4 color)
		:m_Pos(x, y, z), m_Color(color){}

	PosColor(Point3 pos, float r, float g, float b, float a)
		:m_Pos(pos), m_Color(r, g, b, a){}

	Point3 m_Pos;
	Color4 m_Color;
};


NS_EEL_END