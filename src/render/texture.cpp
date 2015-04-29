#include "texture.h"
#include "utility/debug.h"
#include "base/renderer.h"

USING_NS_EEL;

Texture::operator ID3D11Texture2D*()
{
	return m_Texture;
}

eel::Texture::Texture(float width, float height)
{
	D3D11_TEXTURE2D_DESC textureDesc;

	textureDesc.Width = (UINT)width;
	textureDesc.Height = (UINT)height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//4x MSAA를 쓰나 안쓰나 검사
	if (Renderer::GetInstance()->GetIsEnable4xMsaa())
	{
		textureDesc.SampleDesc.Count = 4;
		textureDesc.SampleDesc.Quality = 
			Renderer::GetInstance()->Get4xMsaaQuality()- 1;
	}
	else
	{
		textureDesc.SampleDesc.Count = 1;
		textureDesc.SampleDesc.Quality = 0;
	}

	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	HR(Renderer::GetInstance()->GetDevice()->
		CreateTexture2D(&textureDesc, 0, &m_Texture));
}

eel::Texture::Texture(ID3D11Texture2D* texture)
: m_Texture(texture)
{

}

eel::Texture::~Texture()
{
	SAFE_RELEASE(m_Texture);
}
