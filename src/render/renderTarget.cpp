#include "renderTarget.h"
#include "utility/debug.h"
#include "base/renderer.h"

USING_NS_EEL;

eel::RenderTarget::RenderTarget(UPTR<Texture> backBuffer, UPTR<Texture> depthStencilBuffer,
	float width, float height,
	float topLeftX, float topLeftY,
	float minDepth, float maxDepth)
: m_View(nullptr), m_DepthStencil(nullptr), 
m_Background(1.0f,1.0f,1.0f,1.0f),
m_DepthStencilBuffer(std::move(depthStencilBuffer)),
m_Camera(nullptr)
{
	HR(Renderer::GetInstance()->GetDevice()
		->CreateRenderTargetView(*backBuffer, 0, &m_View));

	HR(Renderer::GetInstance()->GetDevice()
		->CreateDepthStencilView(*m_DepthStencilBuffer, 0, &m_DepthStencil));

	//set viewport

	m_Viewport.TopLeftX = topLeftX;
	m_Viewport.TopLeftY = topLeftY;
	m_Viewport.Width = width;
	m_Viewport.Height = height;
	m_Viewport.MinDepth = minDepth;
	m_Viewport.MaxDepth = maxDepth;
}

eel::RenderTarget::~RenderTarget()
{
	SAFE_DELETE(m_Camera);
	SAFE_RELEASE(m_View);
	SAFE_RELEASE(m_DepthStencil);
}

void eel::RenderTarget::BeginFrame()
{
	Renderer::GetInstance()->GetContext()->
		RSSetViewports(1, &m_Viewport);

	Renderer::GetInstance()->GetContext()->
		ClearRenderTargetView(m_View,
		m_Background.GetArray().data());

	Renderer::GetInstance()->GetContext()->
		ClearDepthStencilView(m_DepthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//bind render target & depthstencil to pipeline

	Renderer::GetInstance()->GetContext()
		->OMSetRenderTargets(1, &m_View, m_DepthStencil);
}
