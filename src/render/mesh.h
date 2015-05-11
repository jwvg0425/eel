#pragma once
#include "d3dx11Effect.h"
#include "base/macro.h"
#include <vector>

class Mesh
{
public:
	UINT GetIndex(UINT idx)
	{
		return m_Indices[idx];
	}

private:
	std::vector<UINT> m_Indices;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_IndexBuffer = nullptr;
	bool m_IsDynamic = false;
	int m_Stride = 0;
};

template<typename Vertex>
class MeshImpl : public Mesh
{
public:
	MeshImpl(std::vector<Vertex>& vertices, std::vector<UINT>& indices)
		: m_Vertices(vertices), m_Indices(indices)
	{
		BuildBuffer();
	}

	MeshImpl(std::vector<Vertex>& vertices, std::vector<UINT>& indices, bool isDynamic)
		: m_Vertices(vertices), m_Indices(indices), m_IsDynamic(isDynamic)
	{
		BuildBuffer();
	}

	Vertex GetVertex(UINT idx)
	{
		return m_Vertices[idx];
	}

private:
	void BuildBuffer()
	{
		D3D11_BUFFER_DESC vbd;

		if (m_IsDynamic)
		{
			vbd.Usage = D3D11_USAGE_DYNAMIC;
		}
		else
		{
			vbd.Usage = D3D11_USAGE_IMMUTABLE;
		}

		m_Stride = sizeof(Vertex);
		vbd.ByteWidth = sizeof(Vertex)* m_Vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		if (m_IsDynamic)
		{
			vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			vbd.CPUAccessFlags = 0;
		}

		vbd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA vinitData;
		vinitData.pSysMem = &m_Vertices[0];
		HR(Renderer::GetInstance()->GetDevice()->CreateBuffer(&vbd, &vinitData, &m_VertexBuffer));

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT)* m_Indices.size();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = &m_Indices[0];
		HR(Renderer::GetInstance()->GetDevice()->CreateBuffer(&ibd, &iinitData, &m_IndexBuffer));
	}

	std::vector<Vertex> m_Vertices;
};