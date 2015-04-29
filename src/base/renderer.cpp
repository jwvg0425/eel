#include "renderer.h"
#include "base/application.h"
#include "debug/debug.h"
#include "component/scene.h"

USING_NS_EEL;

eel::Renderer::Renderer()
{
	_ASSERT(Init());
}

eel::Renderer::~Renderer()
{
	if (m_D3DImmediateContext)
	{
		m_D3DImmediateContext->ClearState();
	}

	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_DepthStencilBuffer);
	SAFE_RELEASE(m_D3DImmediateContext);
	SAFE_RELEASE(m_D3DDevice);
}

bool eel::Renderer::Init()
{
	ARRAY<float, 4> bgColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_BackgroundColor.SetArray(bgColor);

	ZeroMemory(&m_ScreenViewport, sizeof(D3D11_VIEWPORT));

	UINT createDeviceFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		m_D3DDriverType,
		0,
		createDeviceFlags,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&m_D3DDevice,
		&featureLevel,
		&m_D3DImmediateContext);

	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	HR(m_D3DDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality));
	_ASSERT(m_4xMsaaQuality > 0);

	DXGI_SWAP_CHAIN_DESC sd;

	sd.BufferDesc.Width = (UINT)Application::GetInstance()->GetWidth();
	sd.BufferDesc.Height = (UINT)Application::GetInstance()->GetHeight();
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (m_IsEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = Application::GetInstance()->GetWindowHandle();
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	IDXGIDevice* dxgiDevice = nullptr;
	HR(m_D3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	HR(dxgiFactory->CreateSwapChain(m_D3DDevice, &sd, &m_SwapChain));

	SAFE_RELEASE(dxgiDevice);
	SAFE_RELEASE(dxgiAdapter);
	SAFE_RELEASE(dxgiFactory);

	InitRenderTarget();

	return true;
}

void eel::Renderer::InitRenderTarget()
{
	_ASSERT(m_D3DImmediateContext);
	_ASSERT(m_D3DDevice);
	_ASSERT(m_SwapChain);

	//오래된 뷰, 깊이 스텐실 버퍼 제거

	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_DepthStencilBuffer);

	//스왑 체인 크기 변경 후 렌더 타겟 뷰 재생성

	auto width = Application::GetInstance()->GetWidth();
	auto height = Application::GetInstance()->GetHeight();

	HR(m_SwapChain->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer = nullptr;
	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_D3DDevice->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView));
	SAFE_RELEASE(backBuffer);

	// 깊이, 스텐실 버퍼 다시 만들기

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = (UINT)width;
	depthStencilDesc.Height = (UINT)height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	//4x MSAA를 쓰나 안쓰나 검사
	if (m_IsEnable4xMsaa)
	{
		depthStencilDesc.SampleDesc.Count = 4;
		depthStencilDesc.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	else
	{
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	HR(m_D3DDevice->CreateTexture2D(&depthStencilDesc, 0, &m_DepthStencilBuffer));
	HR(m_D3DDevice->CreateDepthStencilView(m_DepthStencilBuffer, 0, &m_DepthStencilView));

	//렌더 타겟 뷰와 깊이 스텐실 뷰를 파이프라인에서 묶음

	m_D3DImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//뷰포트 변환 설정

	m_ScreenViewport.TopLeftX = 0.0f;
	m_ScreenViewport.TopLeftY = 0.0f;
	m_ScreenViewport.Width = width;
	m_ScreenViewport.Height = height;
	m_ScreenViewport.MinDepth = 0.0f;
	m_ScreenViewport.MaxDepth = 1.0f;

	m_D3DImmediateContext->RSSetViewports(1, &m_ScreenViewport);
}

void eel::Renderer::Render(SPTR<Scene> scene)
{
	HR(m_SwapChain->Present(0, 0));
}

void eel::Renderer::BeginFrame()
{
	_ASSERT(m_D3DImmediateContext);
	_ASSERT(m_SwapChain);

	m_D3DImmediateContext->
		ClearRenderTargetView(m_RenderTargetView, 
		m_BackgroundColor.GetArray().data());

	m_D3DImmediateContext->
		ClearDepthStencilView(m_DepthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void eel::Renderer::Update(float dTime)
{

}

ID3D11Device* eel::Renderer::GetDevice() const
{
	return m_D3DDevice;
}

ID3D11DeviceContext* eel::Renderer::GetContext() const
{
	return m_D3DImmediateContext;
}
