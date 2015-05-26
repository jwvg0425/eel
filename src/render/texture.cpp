#include "texture.h"
#include "utility/debug.h"
#include "base/renderer.h"

USING_NS_EEL;

Texture::operator ID3D11Texture2D*()
{
	return m_Texture;
}

eel::Texture::Texture(float width, float height, UINT bindFlags)
	:m_Texture(nullptr), m_Type(TextureType::NORMAL)
{
	m_Desc.Width = (UINT)width;
	m_Desc.Height = (UINT)height;
	m_Desc.MipLevels = 1;
	m_Desc.ArraySize = 1;
	m_Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//4x MSAA check
	if (Renderer::GetInstance()->GetIsEnable4xMsaa())
	{
		m_Desc.SampleDesc.Count = 4;
		m_Desc.SampleDesc.Quality =
			Renderer::GetInstance()->Get4xMsaaQuality() - 1;
	}
	else
	{
		m_Desc.SampleDesc.Count = 1;
		m_Desc.SampleDesc.Quality = 0;
	}

	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = bindFlags;
	m_Desc.CPUAccessFlags = 0;
	m_Desc.MiscFlags = 0;

	HR(Renderer::GetInstance()->GetDevice()->
		CreateTexture2D(&m_Desc, 0, &m_Texture));
}

eel::Texture::Texture(ID3D11Texture2D* texture)
	: m_Texture(texture), m_Type(TextureType::NORMAL)
{

}

eel::Texture::Texture(float width, float height, UINT bindFlags, TextureType type)
	:m_Texture(nullptr), m_Type(type)
{
	m_Desc.Width = (UINT)width;
	m_Desc.Height = (UINT)height;
	m_Desc.MipLevels = 0;
	
	switch (type)
	{
	case TextureType::NORMAL:
		m_Desc.ArraySize = 1;
		m_Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		break;
	case TextureType::CUBE:
		m_Desc.ArraySize = 6;
		m_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		break;
	}

	//4x MSAA check
	if (Renderer::GetInstance()->GetIsEnable4xMsaa())
	{
		m_Desc.SampleDesc.Count = 4;
		m_Desc.SampleDesc.Quality =
			Renderer::GetInstance()->Get4xMsaaQuality() - 1;
	}
	else
	{
		m_Desc.SampleDesc.Count = 1;
		m_Desc.SampleDesc.Quality = 0;
	}

	m_Desc.Usage = D3D11_USAGE_DEFAULT;
	m_Desc.BindFlags = bindFlags;
	m_Desc.CPUAccessFlags = 0;

	switch (type)
	{
	case TextureType::NORMAL:
		m_Desc.MiscFlags = 0;
		break;
	case TextureType::CUBE:
		m_Desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
		break;
	}

	HR(Renderer::GetInstance()->GetDevice()->
		CreateTexture2D(&m_Desc, 0, &m_Texture));
}

eel::Texture::~Texture()
{
	SAFE_RELEASE(m_Texture);
}

const D3D11_TEXTURE2D_DESC& eel::Texture::GetDesc() const
{
	return m_Desc;
}
