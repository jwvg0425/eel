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

	operator ID3D11Texture2D*();

private:
	ID3D11Texture2D* m_Texture = nullptr;
};

NS_EEL_END