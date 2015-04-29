#pragma once
#include "d3dx11Effect.h"
#include "base/object.h"
#include "render/texture.h"

NS_EEL_BEGIN

class RenderTarget : public Object
{
public:
	RenderTarget();
	~RenderTarget() override;

	RenderTarget(RenderTarget& rhs) = delete;
	RenderTarget& operator=(RenderTarget& rhs) = delete;

private:
	UPTR<Texture>			m_DepthStencilBuffer = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	D3D11_VIEWPORT m_Viewport;
};

NS_EEL_END