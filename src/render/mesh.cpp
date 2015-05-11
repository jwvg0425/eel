#include "Mesh.h"


USING_NS_EEL;


Mesh::Mesh()
	:m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_IsDynamic(false), m_Stride(0)
{

}

UINT eel::Mesh::GetIndex(UINT idx)
{
	return m_Indices[idx];
}

