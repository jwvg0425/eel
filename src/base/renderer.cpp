#include "renderer.h"
#include "base/application.h"
#include "utility/debug.h"
#include "component/scene.h"
#include "render/texture.h"
#include "render/effect.h"
#include "base/director.h"
#include "render/light/directionalLight.h"
#include "render/light/pointLight.h"
#include "render/light/spotLight.h"

USING_NS_EEL;

eel::Renderer::Renderer()
{
	_ASSERT(Init());
	RegisterDefaultEffect();
	Director::GetInstance()->RegisterEvent(EventType::UPDATE, this, &Renderer::Update);
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

	//remove old render target
	m_ScreenRenderTarget = nullptr;

	//cbange swap chain size

	auto width = Application::GetInstance()->GetWidth();
	auto height = Application::GetInstance()->GetHeight();

	HR(m_SwapChain->ResizeBuffers(1, (UINT)width, (UINT)height, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer = nullptr;
	HR(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));


	// recreate render target 
	m_ScreenRenderTarget = 
		RenderTarget::Create(Texture::Create(backBuffer),
		Texture::Create(width, height), width, height);
}

void eel::Renderer::Render(SPTR<Scene> scene)
{
	_ASSERT(scene != nullptr);

	m_CurrentRenderTarget = m_ScreenRenderTarget.get();
	m_ScreenRenderTarget->BeginFrame();

	scene->Render();

	//draw to registered render target

	for (auto& renderTarget : m_RenderTargets)
	{
		m_CurrentRenderTarget = renderTarget.get();
		renderTarget->BeginFrame();
		scene->Render();
	}

	HR(m_SwapChain->Present(0, 0));
}

void eel::Renderer::Update(const UpdateEvent& e)
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

void eel::Renderer::SetScreenBackgroundColor(Color4 color)
{
	m_ScreenRenderTarget->SetBackground(color);
}

void eel::Renderer::SetScreenCamera(UPTR<Camera> camera)
{
	m_ScreenRenderTarget->SetCamera(std::move(camera));
}

void eel::Renderer::RegisterEffect(const std::string& effectName, UPTR<Effect> effect)
{
	EffectPair pair;
	pair.first = effectName;
	pair.second = std::move(effect);
	m_Effects.emplace_back(std::move(pair));
}

Effect* eel::Renderer::GetEffect(const std::string& effectName)
{
	for (auto& effect : m_Effects)
	{
		if (effect.first == effectName)
		{
			return effect.second.get();
		}
	}

	return nullptr;
}

void eel::Renderer::RegisterDefaultEffect()
{
	//simple color
	auto effect = Effect::Create(L"fx/color.cso", "ColorTech");
	InputLayout inputLayout;

	inputLayout.AddSemantic("POSITION", 0, SemanticType::RGB_FLOAT32);
	inputLayout.AddSemantic("COLOR", 0, SemanticType::RGBA_FLOAT32);

	effect->AddTech("ColorTech", inputLayout);
	effect->AddMatrixMember("gWorldViewProj");

	RegisterEffect("SimpleColor", std::move(effect));

	//simple light
	auto rightEffect = Effect::Create(L"fx/light.cso", "Light");
	InputLayout rightInputLayout;

	rightInputLayout.AddSemantic("POSITION", 0, SemanticType::RGB_FLOAT32);
	rightInputLayout.AddSemantic("NORMAL", 0, SemanticType::RGB_FLOAT32);

	rightEffect->AddTech("Light", rightInputLayout);
	rightEffect->AddMatrixMember("gWorldViewProj");
	rightEffect->AddMatrixMember("gWorld");
	rightEffect->AddMatrixMember("gWorldInvTranspose");

	rightEffect->AddVectorMember("gEyePosW");

	rightEffect->AddGenericMember("gMaterial");

	rightEffect->AddLightMember<DirectionalLight>("gDirLight", "gDirLightNum", 3);
	rightEffect->AddLightMember<PointLight>("gPointLight", "gPointLightNum", 3);
	rightEffect->AddLightMember<SpotLight>("gSpotLight", "gSpotLightNum", 3);

	RegisterEffect("SimpleLight", std::move(rightEffect));
}

void eel::Renderer::SetInputLayout(ID3D11InputLayout* inputLayout)
{
	m_D3DImmediateContext->IASetInputLayout(inputLayout);
}

void eel::Renderer::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	m_D3DImmediateContext->IASetPrimitiveTopology(topology);
}

Camera* eel::Renderer::GetCurrentCamera()
{
	_ASSERT(m_CurrentRenderTarget != nullptr);

	return m_CurrentRenderTarget->GetCamera();
}

void eel::Renderer::RegisterRenderTarget(SPTR<RenderTarget> renderTarget)
{
	m_RenderTargets.push_back(renderTarget);
}

bool eel::Renderer::UnregisterRenderTarget(SPTR<RenderTarget> renderTarget)
{
	for (auto it = m_RenderTargets.cbegin(); it != m_RenderTargets.cend(); ++it)
	{
		if (*it == renderTarget)
		{
			it = m_RenderTargets.erase(it);
			return true;
		}
	}

	return false;
}
