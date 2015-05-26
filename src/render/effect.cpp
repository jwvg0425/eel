#include "effect.h"
#include <fstream>
#include "base/renderer.h"
#include "utility/debug.h"
#include "base/director.h"

USING_NS_EEL;

Effect::Effect(const std::wstring& filePath, const std::string defaultTech)
	:m_DefaultTech(defaultTech)
{
	std::ifstream fin(filePath, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int) fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, Renderer::GetInstance()->GetDevice(), &m_Fx);

	Director::GetInstance()->RegisterEvent(EventType::UPDATE, this, &Effect::Update);
}

void eel::Effect::AddGenericMember(const std::string& memberName)
{
	GenericPair pair;
	pair.first = memberName;
	pair.second = m_Fx->GetVariableByName(pair.first.c_str());
	m_GenericValues.push_back(pair);
}

void eel::Effect::AddVectorMember(const std::string& memberName)
{
	VectorPair pair;
	pair.first = memberName;
	pair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsVector();
	m_Vectors.push_back(pair);

}

void eel::Effect::AddMatrixMember(const std::string& memberName)
{
	MatrixPair pair;
	pair.first = memberName;
	pair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsMatrix();
	m_Matrixes.push_back(pair);
}

void eel::Effect::AddResourceMember(const std::string& memberName)
{
	ResourcePair pair;
	pair.first = memberName;
	pair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsShaderResource();
	m_Resources.push_back(pair);
}

void eel::Effect::AddTech(const std::string& memberName, const InputLayout& inputLayout)
{
	TechData data;
	
	data.m_Tech = m_Fx->GetTechniqueByName(memberName.c_str());
	data.m_InputLayout = inputLayout.GetLayout(data.m_Tech);
	TechPair pair(memberName, data);
	m_Techs.push_back(pair);
}

void eel::Effect::SetVectorMember(const std::string& memberName, const Vector4& value)
{
	for (auto pair : m_Vectors)
	{
		if (pair.first == memberName)
		{
			pair.second->SetRawValue(&value, 0, sizeof(XMFLOAT3));
			return;
		}
	}
}

void eel::Effect::SetMatrixMember(const std::string& memberName, const Matrix4& value)
{
	for (auto pair : m_Matrixes)
	{
		if (pair.first == memberName)
		{
			pair.second->SetMatrix(reinterpret_cast<const float*>(&value));
			return;
		}
	}
}

void eel::Effect::SetResourceMember(const std::string& memberName,const ShaderResource& value)
{
	for (auto pair : m_Resources)
	{
		if (pair.first == memberName)
		{
			pair.second->SetResource(value);
			return;
		}
	}
}

TechData eel::Effect::GetTech(const std::string& techName)
{
	for (auto pair : m_Techs)
	{
		if (pair.first == techName)
		{
			return pair.second;
		}
	}

	_ASSERT(false);
	return m_Techs[0].second;
}

eel::TechData eel::Effect::GetTech()
{
	return GetTech(m_DefaultTech);
}

eel::Effect::~Effect()
{
	SAFE_RELEASE(m_Fx);

	for (auto pair : m_Techs)
	{
		SAFE_RELEASE(pair.second.m_InputLayout);
	}
}

void eel::Effect::SetUpdateFunc(EffectUpdateFunc func)
{
	m_Updater = func;
}

void eel::Effect::Update(const UpdateEvent& e)
{
	if (m_Updater != nullptr)
	{
		m_Updater(this);
	}
}
