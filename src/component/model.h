#pragma once
#include "component/component.h"
#include "render/mesh.h"
#include "math/matrix.h"
#include "utility/makeCreate.h"
#include <functional>

NS_EEL_BEGIN

class Effect;

class Model : public Component, public MakeCreate<Model>
{
public:
	using RenderUpdateFunc = std::function < void(const Model*, Effect*) > ;
	template<typename Vertex>
	Model(std::vector<Vertex> vertices, std::vector<UINT> indices)
		:m_Effect(nullptr)
	{
		m_Mesh = std::make_unique<MeshImpl<Vertex>>(vertices, indices);
	}
	
	Model(std::string meshFilePath);

	template<typename Vertex>
	Vertex GetVertex(UINT idx) const
	{
		return static_cast<MeshImpl<Vertex>>(m_Mesh)->GetVertex(idx);
	}

	void SetRenderUpdate(RenderUpdateFunc func);
	void SetTech(const std::string& techName);

	UINT GetIndex(UINT idx) const;
	Matrix4 GetWorld() const;

	virtual void Render() const;

private:
	UPTR<Mesh> m_Mesh = nullptr;
	WRITE_ONLY(Effect*, Effect);
	RenderUpdateFunc m_Func = nullptr;
	std::string m_TechName = "";

	Matrix4		m_World;
};

NS_EEL_END