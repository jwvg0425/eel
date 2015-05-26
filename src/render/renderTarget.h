#pragma once
#include "d3dx11Effect.h"
#include "base/object.h"
#include "render/texture.h"
#include "math/vector.h"
#include "render/camera/camera.h"

NS_EEL_BEGIN

class RenderTarget : public Object
{
public:
	RenderTarget(SPTR<Texture> backBuffer, SPTR<Texture> depthStencilBuffer,
		float width, float height,
		float topLeftX = 0.0f, float topLeftY = 0.0f,
		float minDepth = 0.0f, float maxDepth = 1.0f,
		bool is2DArrayTexture = false, int arraySlice = 0);
	~RenderTarget() override;

	RenderTarget(RenderTarget& rhs) = delete;
	RenderTarget& operator=(RenderTarget& rhs) = delete;

	void BeginFrame();
	void SetCamera(SPTR<Camera> camera);
	Camera* GetCamera() const;
	void AddIgnoreList(Object* object);
	bool IsIgnore(SPTR<Object> object);

	CREATE_FUNC(RenderTarget);

private:
	SPTR<Texture>			m_DepthStencilBuffer = nullptr;

	READ_ONLY(ID3D11RenderTargetView*, View);
	READ_ONLY(ID3D11DepthStencilView*, DepthStencil);
	D3D11_VIEWPORT			m_Viewport;

	PROPERTY(Color4, Background);
	SPTR<Camera> m_Camera = nullptr;
	std::vector<Object*> m_IgnoreList;
};

NS_EEL_END