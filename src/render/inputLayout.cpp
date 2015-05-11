#include "inputLayout.h"
#include "utility/debug.h"
#include "base/renderer.h"

USING_NS_EEL;


void InputLayout::AddSemantic(const std::string& semantic, UINT semanticIdx, SemanticType type)
{
	D3D11_INPUT_ELEMENT_DESC desc =
	{ semantic.c_str(), semanticIdx, (DXGI_FORMAT)type, 0, m_Offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	m_Desc.emplace_back(desc);

	AddOffset(type);
}

void eel::InputLayout::AddOffset(SemanticType type)
{
	switch (type)
	{
	case SemanticType::R_FLOAT16:
		m_Offset += 2;
		break;
	case SemanticType::R_FLOAT32:
	case SemanticType::RG_FLOAT16:
		m_Offset += 4;
		break;
	case SemanticType::RG_FLOAT32:
	case SemanticType::RGBA_FLOAT16:
		m_Offset += 8;
		break;
	case SemanticType::RGB_FLOAT32:
		m_Offset += 12;
		break;
	case SemanticType::RGBA_FLOAT32:
		m_Offset += 16;
		break;
	}
}

ID3D11InputLayout* eel::InputLayout::GetLayout(ID3DX11EffectTechnique* tech) const
{
	D3DX11_PASS_DESC desc;
	tech->GetPassByIndex(0)->GetDesc(&desc);
	ID3D11InputLayout* layout = nullptr;
	HR(Renderer::GetInstance()->GetDevice()->CreateInputLayout(m_Desc.data(), m_Desc.size(), desc.pIAInputSignature,
		desc.IAInputSignatureSize, &layout));

	return layout;
}
