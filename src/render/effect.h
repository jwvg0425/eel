#pragma once
#include "base/macro.h"
#include "utility/singleton.h"
#include <d3dx11Effect.h>
#include <vector>
#include <string>
#include "math/vector.h"
#include "math/matrix.h"
// const buffer / tech list
// getVariable, setVariable,

NS_EEL_BEGIN

enum class EffectValueType
{
	GENERIC,
	VECTOR,
	MATRIX,
	RESOURCE,
	TECH,
};

struct TechData
{
	TechData(ID3DX11EffectTechnique* tech, ID3D11InputLayout* inputLayout)
		: m_Tech(tech), m_InputLayout(inputLayout) {}

	ID3DX11EffectTechnique* m_Tech;
	ID3D11InputLayout* m_InputLayout;
};

class Effect
{
public:
	using TechPair = std::pair < std::string, TechData > ;
	using TypePair = std::pair < std::string, EffectValueType > ;
	using MatrixPair = std::pair < std::string, ID3DX11EffectMatrixVariable* > ;
	using VectorPair = std::pair < std::string, ID3DX11EffectVectorVariable* > ;
	using GenericPair = std::pair < std::string, ID3DX11EffectVariable* > ;
	using ResourcePair = std::pair < std::string, ID3DX11EffectShaderResourceVariable* > ;

public:
	Effect(const std::wstring& fileName);
	~Effect();

	void	AddGenericMember(const std::string& memberName);
	void	AddVectorMember(const std::string& memberName);
	void	AddMatrixMember(const std::string& memberName);
	void	AddResourceMember(const std::string& memberName);
	//TODO : ID3D11InputLayout* -> const InputLayout& (wrapper class)
	void	AddTech(const std::string& memberName, ID3D11InputLayout* inputLayout);

	template<typename T>
	void	SetGenericMember(const std::string& memberName, T value, UINT valueSize);

	void	SetVectorMember(const std::string& memberName, const Vector4& value);
	void	SetMatrixMember(const std::string& memberName, const Matrix4& value);
	//TODO : ID3D11ShaderResourceView* -> const ShaderResource& (wrapper class)
	void	SetResourceMember(const std::string& memberName, ID3D11ShaderResourceView* value);

	TechData GetTech(const std::string& techName);

private:
	ID3DX11Effect* m_Fx = nullptr;
	std::vector<TechPair> m_Techs;
	std::vector<MatrixPair> m_Matrixes;
	std::vector<VectorPair> m_Vectors;
	std::vector<GenericPair> m_GenericValues;
	std::vector<ResourcePair> m_Resources;
};

template<typename T>
void eel::Effect::SetGenericMember(const std::string& memberName, T value, UINT valueSize)
{

	for (auto pair : m_GenericValues)
	{
		if (pair.first == memberName)
		{
			pair.second->SetRawValue(&value, 0, valueSize);
			return;
		}
	}
}

NS_EEL_END