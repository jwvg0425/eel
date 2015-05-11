﻿#pragma once
#include "d3dx11Effect.h"
#include "component/scene.h"
#include "math/vector.h"
#include "utility/singleton.h"
#include "render/renderTarget.h"
#include <vector>

NS_EEL_BEGIN
class Effect;
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
	void SetScreenCamera(Camera* camera);

	void RegisterEffect(const std::string& effectName, UPTR<Effect> effect);
	Effect* GetEffect(const std::string& effectName);

	ID3D11Device*			GetDevice() const;
	ID3D11DeviceContext*	GetContext() const;

private:
	void RegisterDefaultEffect();
	ID3D11Device* m_D3DDevice = nullptr;
	ID3D11DeviceContext* m_D3DImmediateContext = nullptr;

	IDXGISwapChain* m_SwapChain = nullptr;
	UPTR<RenderTarget> m_ScreenRenderTarget = nullptr;
	D3D_DRIVER_TYPE m_D3DDriverType = D3D_DRIVER_TYPE_HARDWARE;

	using EffectPair = std::pair < std::string, UPTR<Effect> > ;

	std::vector<EffectPair> m_Effects;
	
	READ_ONLY(bool, IsEnable4xMsaa);
	READ_ONLY(UINT, 4xMsaaQuality);
};

NS_EEL_END