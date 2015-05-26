#pragma once
#include "component/component.h"
#include "render/mesh.h"
#include "math/matrix.h"
#include "render/light/material.h"
#include <functional>
#include "math/ray.h"
#include "render/shaderResource.h"

NS_EEL_BEGIN

class Effect;
using MaterialTuple = std::tuple < std::string, UPTR<Material>, UINT >;

class Model : public Component
{
public:
	using RenderUpdateFunc = std::function < void(const Model*, Effect*) > ;
	template<typename Vertex>
	Model(std::vector<Vertex> vertices, std::vector<UINT> indices)
		:m_Effect(nullptr), m_Topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
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

	MaterialData GetMaterial(const std::string& name) const;

	void AddShaderResource(const std::string& name, const std::string& path);

	const ShaderResource& GetShaderResource(const std::string& name) const;

	/// if fails it will return -1, or return index of triangle
	int CheckWithRay(const Ray& ray, OUT float& minDist) const override;
	int CheckWithRay(const Ray& ray) const override;

	CREATE_FUNC(Model);

	void SetPosition(float x, float y, float z);
	void SetScaleRate(float scaleX, float scaleY, float scaleZ);
	void SetRotateAngle(float angleX, float angleY, float angleZ);

	void UpdateWorld();

private:
	UPTR<Mesh> m_Mesh = nullptr;
	WRITE_ONLY(Effect*, Effect);
	RenderUpdateFunc m_Func = nullptr;
	std::string m_TechName = "";
	std::vector<MaterialTuple> m_Materials;

	using ResourcePair = std::pair < std::string, ShaderResource > ;
	std::vector<ResourcePair> m_ShaderResources;

	PROPERTY(D3D_PRIMITIVE_TOPOLOGY, Topology);
	READ_ONLY(Matrix4, World);
	Matrix4		m_Translation;
	Matrix4		m_Scaling;
	Matrix4		m_Rotation;

	READ_ONLY(Vector3, Position);
	READ_ONLY(Vector3, ScaleRate);
	READ_ONLY(Vector3, RotateAngle);
};

NS_EEL_END