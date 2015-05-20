#pragma once
#include "base/macro.h"
#include "math/vector.h"

NS_EEL_BEGIN


//just interface
struct Material
{
};

struct LightMaterial : public eel::Material
{
	Color4 m_Ambient;
	Color4 m_Diffuse;
	Color4 m_Specular;
	Color4 m_Reflect;
};

struct MaterialData
{
	Material* m_Material;
	UINT m_Size;
};

NS_EEL_END