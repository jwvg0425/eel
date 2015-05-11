#pragma once
#include <d3dx11Effect.h>
#include <vector>
#include <string>
#include "base/macro.h"

NS_EEL_BEGIN

enum class SemanticType
{
	R_FLOAT16 = DXGI_FORMAT_R16_FLOAT,
	RG_FLOAT16 = DXGI_FORMAT_R16G16_FLOAT,
	RGBA_FLOAT16 = DXGI_FORMAT_R16G16B16A16_FLOAT,
	R_FLOAT32 = DXGI_FORMAT_R32_FLOAT,
	RG_FLOAT32 = DXGI_FORMAT_R32G32_FLOAT,
	RGB_FLOAT32 = DXGI_FORMAT_R32G32B32_FLOAT,
	RGBA_FLOAT32 = DXGI_FORMAT_R32G32B32A32_FLOAT
};

class InputLayout
{
public:
	InputLayout() = default;
	~InputLayout();

	void AddSemantic(const std::string& semantic, UINT semanticIdx, SemanticType type);
	ID3D11InputLayout* GetLayout(ID3DX11EffectTechnique* tech) const;

private:
	void AddOffset(SemanticType type);
	READ_ONLY_REF(std::vector<D3D11_INPUT_ELEMENT_DESC>, Desc);
	UINT m_Offset = 0;
};

NS_EEL_END