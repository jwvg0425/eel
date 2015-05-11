#include "Mesh.h"


USING_NS_EEL;

UINT eel::Mesh::GetIndex(UINT idx) const
{
	return m_Indices[idx];
}

UINT eel::Mesh::GetIndexCount() const
{
	return m_Indices.size();
}

eel::Mesh::Mesh(std::vector<UINT>& indices)
	:m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_IsDynamic(false), m_Stride(0),
	m_Indices(indices)
{

}

eel::Mesh::Mesh(std::vector<UINT>& indices, bool isDynamic)
	:m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_IsDynamic(isDynamic), m_Stride(0),
	m_Indices(indices)
{

}

void eel::Mesh::SetStride(UINT stride)
{
	m_Stride = stride;
}

void eel::Mesh::SetBuffer(ID3D11Buffer* vertex, ID3D11Buffer* index)
{
	m_VertexBuffer = vertex;
	m_IndexBuffer = index;
}

UINT* eel::Mesh::GetIndexHead()
{
	return &m_Indices[0];
}

eel::Mesh::~Mesh()
{
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_IndexBuffer);
}

