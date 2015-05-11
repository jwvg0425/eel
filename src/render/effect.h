#pragma once
#include "base/macro.h"
#include "utility/singleton.h"
#include <d3dx11Effect.h>
#include <vector>
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

class EffectImpl
{
public:
	using TechPair = std::pair < std::string, ID3DX11EffectTechnique* > ;
	using TypePair = std::pair < std::string, EffectValueType > ;
	using MatrixPair = std::pair < std::string, ID3DX11EffectMatrixVariable* > ;
	using VectorPair = std::pair < std::string, ID3DX11EffectVectorVariable* > ;
	using GenericPair = std::pair < std::string, ID3DX11EffectVariable* > ;
	using ResourcePair = std::pair < std::string, ID3DX11EffectShaderResourceVariable* > ;

public:

	EffectImpl(const std::wstring& fileName, std::vector<EffectImpl::TypePair>& typePairs);
	~EffectImpl();

	template<typename T>
	bool	SetMember(const std::wstring& memberName, T value, EffectValueType valueType, UINT valueSize);
private:
	void	GetNewMember(const TypePair& pair);

private:
	ID3DX11Effect* m_Fx = nullptr;
	std::vector<TechPair> m_Techs;
	std::vector<MatrixPair> m_Matrixes;
	std::vector<VectorPair> m_Vectors;
	std::vector<GenericPair> m_GenericValues;
	std::vector<ResourcePair> m_Resources;
};

template<typename T>
bool eel::EffectImpl::SetMember(const std::wstring& memberName, T value, EffectValueType valueType, UINT valueSize)
{

	switch(valueType)
	{
		case eel::EffectValueType::GENERIC:
		{
			for(auto pair : m_GenericValues)
			{
				if(pair.first == memberName)
				{
					pair.second->SetRawValue(&value, 0, valueSize);
					return true;
				}
			}
			break;
		}
		case eel::EffectValueType::VECTOR:
		{
			for(auto pair : m_Vectors)
			{
				if(pair.first == memberName)
				{
					pair.second->SetRawValue(&value, 0, valueSize);
					return true;
				}
			}
			break;
		}
		case eel::EffectValueType::MATRIX:
		{
			static_assert( std::is_same(T, CXMMATRIX)::value );
			for(auto pair : m_Matrixes)
			{
				if(pair.first == memberName)
				{
					pair.second->SetMatrix(reinterpret_cast<const float*>( &value ));
					return true;
				}
			}
			break;
		}
		case eel::EffectValueType::RESOURCE:
		{
			static_assert( std::is_same(T, ID3D11ShaderResourceView*)::value );
			for(auto pair : m_Resources)
			{
				if(pair.first == memberName)
				{
					pair.second->SetResource(value);
					return true;
				}
			}
			break;
		}
		default:
		break;
	}

	return false;
}

template <typename T>
class Effect : public EffectImpl, public Singleton<T>
{
public:
	Effect(const std::wstring& fxPath, const std::vector<TypePair>& typePairs)
		:EffectImpl(fxPath, typePairs)
	{};
	~Effect();
private:
};

NS_EEL_END