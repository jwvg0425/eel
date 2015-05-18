#pragma once
#include "d3dx11Effect.h"
#include "base/object.h"
#include "utility/debug.h"
#include "math/vector.h"
#include "vertex/vertexUtil.h"
#include <vector>

NS_EEL_BEGIN

class Mesh : public Object
{
public:
	Mesh(std::vector<UINT>& indices);
	Mesh(std::vector<UINT>& indices, bool isDynamic);
	~Mesh();

	UINT GetIndex(UINT idx) const;
	UINT GetIndexCount() const;
	virtual const Point3* GetPosByIndex(UINT idx) const
	{
		return nullptr;
	}

protected:
	void SetStride(UINT stride);
	void SetBuffer(ID3D11Buffer* vertex, ID3D11Buffer* index);
	UINT* GetIndexHead();

private:
	std::vector<UINT> m_Indices;

	READ_ONLY(ID3D11Buffer*, VertexBuffer);
	READ_ONLY(ID3D11Buffer*, IndexBuffer);
	READ_ONLY(bool, IsDynamic);
	READ_ONLY(UINT, Stride);
};

template<typename RawVertex>
class MeshImpl : public Mesh
{
public:
	MeshImpl(std::vector<RawVertex>& vertices, std::vector<UINT>& indices)
		: Mesh(indices)
	{
		BuildBuffer(vertices);
	}

	MeshImpl(std::vector<RawVertex>& vertices, std::vector<UINT>& indices, bool isDynamic)
		: Mesh(indices)
	{
		BuildBuffer(vertices);
	}

	VertexWrapper<RawVertex> GetVertex(UINT idx) const
	{
		return m_Vertices[idx];
	}

	const Point3* GetPosByIndex(UINT idx) const override
	{
		return m_Vertices[idx].GetPos();
	}

private:
	void BuildBuffer(const std::vector<RawVertex>& vertices)
	{
		D3D11_BUFFER_DESC vbd;

		if (GetIsDynamic())
		{
			vbd.Usage = D3D11_USAGE_DYNAMIC;
		}
		else
		{
			vbd.Usage = D3D11_USAGE_IMMUTABLE;
		}

		SetStride(sizeof(RawVertex));
		vbd.ByteWidth = sizeof(RawVertex)* vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		if (GetIsDynamic())
		{
			vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			vbd.CPUAccessFlags = 0;
		}

		vbd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &vertices[0];
		ID3D11Buffer* vertexBuffer = nullptr;
		HR(Renderer::GetInstance()->GetDevice()->CreateBuffer(&vbd, &vinitData, &vertexBuffer));

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT)* GetIndexCount();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = GetIndexHead();
		ID3D11Buffer* indexBuffer = nullptr;
		HR(Renderer::GetInstance()->GetDevice()->CreateBuffer(&ibd, &iinitData, &indexBuffer));

		SetBuffer(vertexBuffer, indexBuffer);

		UINT idx = 0;
		for(auto vertex : vertices)
		{
			m_Vertices.push_back(vertex);
		}
	}

	std::vector<VertexWrapper<RawVertex>>	m_Vertices;
};


NS_EEL_END