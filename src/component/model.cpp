#include "model.h"
#include "render/effect.h"
#include "base/renderer.h"
#include "render/vertex/vertexUtil.h"
#include "math/mathHelper.h"
#include "base/director.h"

USING_NS_EEL;

UINT eel::Model::GetIndex(UINT idx) const
{
	return m_Mesh->GetIndex(idx);
}

void eel::Model::Render() const
{
	if (m_Func != nullptr)
	{
		m_Func(this, m_Effect);
	}

	TechData tech;

	if (m_TechName == "")
	{
		tech = m_Effect->GetTech();
	}
	else
	{
		tech = m_Effect->GetTech(m_TechName);
	}

	Renderer::GetInstance()->SetInputLayout(tech.m_InputLayout);
	Renderer::GetInstance()->SetPrimitiveTopology(m_Topology);

	UINT stride = m_Mesh->GetStride();
	UINT offset = 0;
	ID3D11Buffer* vertexBuffer = m_Mesh->GetVertexBuffer();
	ID3D11Buffer* indexBuffer = m_Mesh->GetIndexBuffer();

	Renderer::GetInstance()->GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Renderer::GetInstance()->GetContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	D3DX11_TECHNIQUE_DESC techDesc;
	tech.m_Tech->GetDesc(&techDesc);

	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech.m_Tech->GetPassByIndex(p)->Apply(0, Renderer::GetInstance()->GetContext());
		Renderer::GetInstance()->GetContext()->DrawIndexed(m_Mesh->GetIndexCount(), 0, 0);
	}
}

void eel::Model::SetRenderUpdate(RenderUpdateFunc func)
{
	m_Func = func;
}

eel::Matrix4 eel::Model::GetWorld() const
{
	return m_World;
}

void eel::Model::SetTech(const std::string& techName)
{
	m_TechName = techName;
}

UINT eel::Model::GetIndexCount() const
{
	return m_Mesh->GetIndexCount();
}

int eel::Model::CheckWithRay(const Ray& ray) const
{
	XMMATRIX W = XMLoadFloat4x4(&m_World.GetValue());
	XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

	Ray testRay;

	testRay.SetRayOrigin(XMVector3TransformCoord(ray.GetRayOrigin(), invWorld));
	testRay.SetRayDirection(XMVector3TransformCoord(ray.GetRayDirection(), invWorld));
	testRay.SetRayDirection(testRay.GetRayDirection().Normalize());

	float tmin = 0.0f;
	int pickedTriangle = -1;
	for(UINT i = 0; i < m_Mesh->GetIndexCount() / 3; ++i)
	{
		tmin = Math::INF;
		// Indices for this triangle.
		UINT i0 = m_Mesh->GetIndex(i * 3 + 0);
		UINT i1 = m_Mesh->GetIndex(i * 3 + 1);
		UINT i2 = m_Mesh->GetIndex(i * 3 + 2);

		// Vertices for this triangle.
		Point3  v0 = *( m_Mesh->GetPosByIndex(i0) );
		Point3	v1 = *( m_Mesh->GetPosByIndex(i1) );
		Point3  v2 = *( m_Mesh->GetPosByIndex(i2) );

		// We have to iterate over all the triangles in order to find the nearest intersection.
		float t = 0.0f;
		if(Math::IntersectRayTriangle(
			ray.GetRayOrigin(),
			ray.GetRayDirection(),
			v0, v1, v2, &t))
		{
			if(t < tmin)
			{
				// This is the new nearest picked triangle.
				tmin = t;
				pickedTriangle = i;
			}
		}
	}

	return pickedTriangle;
}
