#include "renderer.h"
#include "base/application.h"
#include "debug/debug.h"
#include "component/scene.h"
#include "render/texture.h"

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

	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_D3DImmediateContext);
	SAFE_RELEASE(m_D3DDevice);
}

bool eel::Renderer::Init()
{
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

	InitScreenRenderTarget();

	return true;
}

void eel::Renderer::InitScreenRenderTarget()
{
	_ASSERT(m_D3DImmediateContext);
	_ASSERT(m_D3DDevice);
	_ASSERT(m_SwapChain);

	//오래된 뷰, 깊이 스텐실 버퍼 제거
	m_ScreenRenderTarget = nullptr;

	//스왑 체인 크기 변경 후 렌더 타겟 뷰 재생성

	auto width = Application::GetInstance()->GetWidth();
	auto height = Application::GetInstance()->GetHeight();

	HR(m_SwapChain->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer = nullptr;
	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));


	// 깊이, 스텐실 버퍼 다시 만들기
	m_ScreenRenderTarget = 
		RenderTarget::Create(Texture::Create(backBuffer),
		Texture::Create(width, height), width, height);
}

void eel::Renderer::Render(SPTR<Scene> scene)
{
	m_ScreenRenderTarget->BeginFrame();

	HR(m_SwapChain->Present(0, 0));
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

void eel::Renderer::SetScreenBackgroundColor(Color color)
{
	m_ScreenRenderTarget->SetBackground(color);
}
