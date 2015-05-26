#pragma once
#include "d3dx11Effect.h"
#include "base/object.h"

NS_EEL_BEGIN

enum class TextureType
{
	NORMAL,
	CUBE
};

class Texture : public Object
{
public:
	CREATE_FUNC(Texture);

	Texture(float width, float height, UINT bindFlags);
	Texture(float width, float height, UINT bindFlags, TextureType type);
	~Texture() override;

	Texture(ID3D11Texture2D* texture);
	const D3D11_TEXTURE2D_DESC& GetDesc() const;

	operator ID3D11Texture2D*();

private:
	READ_ONLY(ID3D11Texture2D*, Texture);
	D3D11_TEXTURE2D_DESC m_Desc;
	PROPERTY(TextureType, Type);
};

NS_EEL_END