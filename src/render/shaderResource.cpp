#include "shaderResource.h"
#include "utility/debug.h"
#include "base/renderer.h"
#include <d3dx11.h>

USING_NS_EEL;

eel::ShaderResource::ShaderResource(std::string path)
{
	std::wstring wpath(path.begin(), path.end());

	HR(D3DX11CreateShaderResourceViewFromFile(Renderer::GetInstance()->GetDevice(),
		wpath.c_str(), nullptr, nullptr, &m_Resource, nullptr));
}

eel::ShaderResource::ShaderResource(std::wstring path)
{
	HR(D3DX11CreateShaderResourceViewFromFile(Renderer::GetInstance()->GetDevice(),
		path.c_str(), nullptr, nullptr, &m_Resource, nullptr));
}

eel::ShaderResource::ShaderResource(ShaderResource&& rhs)
	:m_Resource(rhs.m_Resource)
{
	rhs.m_Resource = nullptr;
}

eel::ShaderResource::~ShaderResource()
{
	SAFE_RELEASE(m_Resource);
}

ShaderResource& eel::ShaderResource::operator=(ShaderResource&& rhs)
{
	m_Resource = rhs.m_Resource;
	rhs.m_Resource = nullptr;

	return *this;
}

ShaderResource::operator ID3D11ShaderResourceView*() const
{
	return m_Resource;
}