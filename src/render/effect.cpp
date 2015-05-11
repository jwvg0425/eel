#include "effect.h"
#include <fstream>
#include "base\renderer.h"
#include "utility\debug.h"

USING_NS_EEL;

EffectImpl::EffectImpl(const std::wstring& filePath, std::vector<EffectImpl::TypePair>& typePairs)
{
	std::ifstream fin(filePath, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int) fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();

	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 0, Renderer::GetInstance()->GetDevice(), &m_Fx));

	for(auto pair : typePairs)
	{
		GetNewMember(pair);
	}
}

void EffectImpl::GetNewMember(const TypePair& pair)
{
	switch(pair.second)
	{
		case EffectValueType::TECH:
		{
			TechPair newPair;
			newPair.first = pair.first;
			newPair.second = m_Fx->GetTechniqueByName(pair.first.c_str());
			m_Techs.push_back(newPair);
			break;
		}
		case EffectValueType::GENERIC:
		{
			GenericPair newPair;
			newPair.first = pair.first;
			newPair.second = m_Fx->GetVariableByName(pair.first.c_str());
			m_GenericValues.push_back(newPair);
		}
		case EffectValueType::MATRIX:
		{
			MatrixPair newPair;
			newPair.first = pair.first;
			newPair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsMatrix();
			m_Matrixes.push_back(newPair);
		}
		case EffectValueType::VECTOR:
		{
			VectorPair newPair;
			newPair.first = pair.first;
			newPair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsVector();
			m_Vectors.push_back(newPair);
		}
		case EffectValueType::RESOURCE:
		{
			ResourcePair newPair;
			newPair.first = pair.first;
			newPair.second = m_Fx->GetVariableByName(pair.first.c_str())->AsShaderResource();
			m_Resources.push_back(newPair);
		}
		default:
		{
			break;
		}
	}
}
