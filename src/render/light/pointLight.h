#pragma once
#include "render/light/light.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct PointLight : Light < PointLight >
{
	Color4 m_Ambient;
	Color4 m_Diffuse;
	Color4 m_Specular;
	Point3 m_Position;
	float m_Range;

	Vector3 m_Attenuate;
	float m_Pad;
};

NS_EEL_END