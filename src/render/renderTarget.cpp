#include "renderTarget.h"
#include "utility/debug.h"
#include "base/renderer.h"

USING_NS_EEL;

eel::RenderTarget::RenderTarget(SPTR<Texture> backBuffer, SPTR<Texture> depthStencilBuffer,
	float width, float height,
	float topLeftX /*= 0.0f*/, float topLeftY /*= 0.0f*/,
	float minDepth /*= 0.0f*/, float maxDepth /*= 1.0f*/,
	bool is2DArrayTexture /*= false*/, int arraySlice /*= 0*/)
	: m_View(nullptr), m_DepthStencil(nullptr),
	m_Background(1.0f, 1.0f, 1.0f, 1.0f),
	m_DepthStencilBuffer(depthStencilBuffer),
	m_Camera(nullptr)
{
	if (!is2DArrayTexture)
	{
		HR(Renderer::GetInstance()->GetDevice()
			->CreateRenderTargetView(*backBuffer, 0, &m_View));
	}
	else
	{
		D3D11_RENDER_TARGET_VIEW_DESC   rtvDesc;
		rtvDesc.Format = backBuffer->GetDesc().Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		rtvDesc.Texture2DArray.ArraySize = 1;
		rtvDesc.Texture2DArray.MipSlice = 0;
		rtvDesc.Texture2DArray.FirstArraySlice = arraySlice;

		HR(Renderer::GetInstance()->GetDevice()
			->CreateRenderTargetView(*backBuffer, &rtvDesc, &m_View));

	}

	if (!is2DArrayTexture)
	{
		HR(Renderer::GetInstance()->GetDevice()
			->CreateDepthStencilView(*m_DepthStencilBuffer, 0, &m_DepthStencil));
	}
	else
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		dsvDesc.Format = depthStencilBuffer->GetDesc().Format;
		dsvDesc.Flags = 0;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

		HR(Renderer::GetInstance()->GetDevice()
			->CreateDepthStencilView(*m_DepthStencilBuffer, &dsvDesc, &m_DepthStencil));

	}

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
	SAFE_RELEASE(m_View);
	SAFE_RELEASE(m_DepthStencil);
}

void eel::RenderTarget::BeginFrame()
{
	Renderer::GetInstance()->GetContext()->
		ClearRenderTargetView(m_View,
		m_Background.GetArray().data());

	Renderer::GetInstance()->GetContext()->
		ClearDepthStencilView(m_DepthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//bind render target & depthstencil to pipeline

	Renderer::GetInstance()->GetContext()
		->OMSetRenderTargets(1, &m_View, m_DepthStencil);

	Renderer::GetInstance()->GetContext()->
		RSSetViewports(1, &m_Viewport);
}

void eel::RenderTarget::SetCamera(SPTR<Camera> camera)
{
	m_Camera = camera;
}

Camera* eel::RenderTarget::GetCamera() const
{
	return m_Camera.get();
}

void eel::RenderTarget::AddIgnoreList(Object* object)
{
	m_IgnoreList.push_back(object);
}

bool eel::RenderTarget::IsIgnore(SPTR<Object> object)
{
	for (auto& ignore : m_IgnoreList)
	{
		if (object.get() == ignore)
		{
			return true;
		}
	}

	return false;
}
