#pragma once
#include "d3dx11Effect.h"
#include "component/scene.h"
#include "math/vector.h"
#include "utility/singleton.h"
#include "render/renderTarget.h"

NS_EEL_BEGIN

class Renderer : public Object, public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();

	bool Init();
	void Render(SPTR<Scene> scene);
	void Update(float dTime);

	void InitScreenRenderTarget();
	void SetScreenBackgroundColor(Color4 color);

	ID3D11Device*			GetDevice() const;
	ID3D11DeviceContext*	GetContext() const;

private:
	ID3D11Device* m_D3DDevice = nullptr;
	ID3D11DeviceContext* m_D3DImmediateContext = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	UPTR<RenderTarget> m_ScreenRenderTarget = nullptr;
	D3D_DRIVER_TYPE m_D3DDriverType = D3D_DRIVER_TYPE_HARDWARE;
	
	READ_ONLY(bool, IsEnable4xMsaa);
	READ_ONLY(UINT, 4xMsaaQuality);
};

NS_EEL_END