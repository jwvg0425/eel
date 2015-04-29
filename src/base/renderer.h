#pragma once
#include "d3dx11Effect.h"
#include "component/scene.h"
#include "math/vector.h"
#include "utility/singleton.h"

NS_EEL_BEGIN

class Renderer : public Object, public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();

	bool Init();
	void Render(SPTR<Scene> scene);
	void Update(float dTime);

	void InitRenderTarget();

	ID3D11Device*			GetDevice() const;
	ID3D11DeviceContext*	GetContext() const;

private:
	void BeginFrame();

	PROPERTY_REF(Color, BackgroundColor);

	ID3D11Device* m_D3DDevice = nullptr;
	ID3D11DeviceContext* m_D3DImmediateContext = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11Texture2D* m_DepthStencilBuffer = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	D3D11_VIEWPORT m_ScreenViewport;
	D3D_DRIVER_TYPE m_D3DDriverType = D3D_DRIVER_TYPE_HARDWARE;
	
	READ_ONLY(bool, IsEnable4xMsaa);
	READ_ONLY(UINT, 4xMsaaQuality);
};

NS_EEL_END