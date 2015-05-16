#include "render/light/light.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct DirectionalLight : Light <DirectionalLight>
{
	Color4 m_Ambient;
	Color4 m_Diffuse;
	Color4 m_Specular;
	Vector3 m_Direction;
	float m_Pad;
};

NS_EEL_END