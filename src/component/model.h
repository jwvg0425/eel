#pragma once
#include "component/component.h"
#include "render/mesh.h"
#include "math/matrix.h"
#include "render/light/material.h"
#include <functional>
#include "math/ray.h"

NS_EEL_BEGIN

class Effect;
using MaterialTuple = std::tuple < std::string, UPTR<Material>, UINT >;

class Model : public Component
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
	UINT GetIndexCount() const;
	Matrix4 GetWorld() const;

	virtual void Render() const;

	template<typename T>
	void AddMaterial(const std::string& name, const T& material)
	{
		static_assert(std::is_base_of<Material, T>::value, "T must inherit Material.");

		UPTR<Material> mat(nullptr);

		mat.reset(new T(material));
		MaterialTuple pair(name, std::move(mat), sizeof(T));

		m_Materials.push_back(std::move(pair));
	}

	MaterialData GetMaterial(const std::string& name) const
	{
		MaterialData res;
		res.m_Material = nullptr;
		res.m_Size = 0;

		for (auto& material : m_Materials)
		{
			if (std::get<0>(material) == name)
			{
				res.m_Material = std::get<1>(material).get();
				res.m_Size = std::get<2>(material);

				return res;
			}
		}

		_ASSERT(false);

		return res;
	}
	/// if fails it will return -1, or return index of triangle
	int CheckWithRay(const Ray& ray) const;

	CREATE_FUNC(Model);

private:
	UPTR<Mesh> m_Mesh = nullptr;
	WRITE_ONLY(Effect*, Effect);
	RenderUpdateFunc m_Func = nullptr;
	std::string m_TechName = "";
	std::vector<MaterialTuple> m_Materials;
	Matrix4		m_World;
};

NS_EEL_END