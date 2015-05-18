#include "base/macro.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct Material
{
	Color4 m_Ambient;
	Color4 m_Diffuse;
	Color4 m_Specular;
	Color4 m_Reflect;
};

NS_EEL_END