#pragma once
#include "base/macro.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct PosColor
{
	PosColor(Point3 pos, Color4 color)
		:m_Pos(pos), m_Color(color) {}

	Point3 m_Pos;
	Color4 m_Color;
};

NS_EEL_END