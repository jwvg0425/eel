﻿#pragma once
#include "d3dx11Effect.h"
#include "base/object.h"
#include "render/texture.h"
#include "utility/makeCreate.h"
#include "math/vector.h"
#include "render/camera/camera.h"

NS_EEL_BEGIN

class RenderTarget : public Object, public MakeCreate<RenderTarget>
{
public:
	RenderTarget(UPTR<Texture> backBuffer, UPTR<Texture> depthStencilBuffer,
		float width, float height,
		float topLeftX = 0.0f, float topLeftY = 0.0f,
		float minDepth = 0.0f, float maxDepth = 0.0f);
	~RenderTarget() override;

	RenderTarget(RenderTarget& rhs) = delete;
	RenderTarget& operator=(RenderTarget& rhs) = delete;

	void BeginFrame();
	void SetCamera(UPTR<Camera> camera);
	Camera* GetCamera() const;

private:
	UPTR<Texture>			m_DepthStencilBuffer = nullptr;

	READ_ONLY(ID3D11RenderTargetView*, View);
	READ_ONLY(ID3D11DepthStencilView*, DepthStencil);
	D3D11_VIEWPORT			m_Viewport;

	PROPERTY(Color4, Background);
	UPTR<Camera> m_Camera = nullptr;
};

NS_EEL_END