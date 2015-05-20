#pragma once
#include "component/component.h"
#include "render/mesh.h"
#include "math/matrix.h"
#include "utility/makeCreate.h"
#include <functional>
#include "math/ray.h"
#include "math/vector.h"

NS_EEL_BEGIN

class Effect;
enum class Topology
{
	TRIANGLE_LIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	LINE_LIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
};
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
	void SetTopology(D3D_PRIMITIVE_TOPOLOGY topology)
	{
		m_Topology = topology;
	};

	UINT GetIndex(UINT idx) const;
	UINT GetIndexCount() const;
	const Point3* GetPosByIndex(UINT idx) const
	{
		return m_Mesh->GetPosByIndex(idx);
	}
	Matrix4 GetWorld() const;

	virtual void Render() const;

	/// if fails it will return -1, or return index of triangle
	int CheckWithRay(const Ray& ray) const;

private:
	UPTR<Mesh> m_Mesh = nullptr;
	WRITE_ONLY(Effect*, Effect);
	RenderUpdateFunc m_Func = nullptr;
	std::string m_TechName = "";
	D3D_PRIMITIVE_TOPOLOGY	m_Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	Matrix4		m_World;
};

NS_EEL_END