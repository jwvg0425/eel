#pragma once
#include "component/component.h"
#include "render/mesh.h"

NS_EEL_BEGIN

class Effect;

class Model : Component
{
public:
	template<typename Vertex>
	Model(std::vector<Vertex> vertices, std::vector<UINT> indices)
	{
		m_Mesh = std::make_unique<MeshImpl<Vertex>>(vertices, indices);
	}
	
	Model(std::string meshFilePath);

	template<typename Vertex>
	Vertex GetVertex(UINT idx)
	{
		return static_cast<MeshImpl<Vertex>>(m_Mesh)->GetVertex(idx);
	}

	UINT GetIndex(UINT idx);

private:
	UPTR<Mesh> m_Mesh = nullptr;
	Effect* m_Effect = nullptr;
};

NS_EEL_END