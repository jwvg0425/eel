#pragma once
#include <d3dx11Effect.h>
#include <vector>
#include <string>
#include "base/macro.h"
#include "render/texture.h"

NS_EEL_BEGIN

class ShaderResource
{
public:
	ShaderResource()
		:m_Resource(nullptr){}
	ShaderResource(std::string path);
	ShaderResource(std::wstring path);
	ShaderResource(SPTR<Texture> tex);
	~ShaderResource();

	operator ID3D11ShaderResourceView*() const;

	ShaderResource(const ShaderResource& rhs) = delete;
	ShaderResource& operator=(const ShaderResource& rhs) = delete;

	ShaderResource(ShaderResource&& rhs);
	ShaderResource& operator=(ShaderResource&& rhs);

private:
	ID3D11ShaderResourceView* m_Resource = nullptr;
};

NS_EEL_END