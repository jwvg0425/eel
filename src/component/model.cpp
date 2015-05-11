#include "model.h"
#include "render/effect.h"
#include "base/renderer.h"

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

	TechData tech = m_Effect->GetTech();

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

eel::Matrix4 eel::Model::GetWorld() const
{
	return m_World;
}
