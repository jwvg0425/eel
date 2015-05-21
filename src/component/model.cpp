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
	Renderer::GetInstance()->SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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

void eel::Model::SetPosition(float x, float y, float z)
{
	m_Position = Vector3(x, y, z);

	m_Translation = XMMatrixTranslation(x, y, z);

	UpdateWorld();
}

void eel::Model::SetScaleRate(float scaleX, float scaleY, float scaleZ)
{
	m_ScaleRate = Vector3(scaleX, scaleY, scaleZ);

	m_Scaling = XMMatrixScaling(scaleX, scaleY, scaleZ);

	UpdateWorld();
}

void eel::Model::SetRotateAngle(float angleX, float angleY, float angleZ)
{
	m_RotateAngle = Vector3(angleX, angleY, angleZ);

	Matrix4 X = XMMatrixRotationX(angleX);
	Matrix4 Y = XMMatrixRotationY(angleY);
	Matrix4 Z = XMMatrixRotationZ(angleZ);

	m_Rotation = X*Y*Z;

	UpdateWorld();
}

void eel::Model::UpdateWorld()
{
	m_World = m_Scaling * m_Rotation * m_Translation;
}

eel::MaterialData eel::Model::GetMaterial(const std::string& name) const
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

void eel::Model::AddShaderResource(const std::string& name, const std::string& path)
{
	std::pair<std::string, ShaderResource> pair(name, std::move(ShaderResource(path)));

	m_ShaderResources.push_back(std::move(pair));
}

const ShaderResource& eel::Model::GetShaderResource(const std::string& name) const
{
	for (auto& shaderResource : m_ShaderResources)
	{
		if (shaderResource.first == name)
		{
			return shaderResource.second;
		}
	}

	_ASSERT(false);

	return *(new ShaderResource());
}
