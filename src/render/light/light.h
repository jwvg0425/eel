#pragma once
#include "base/object.h"
#include "render/effect.h"

NS_EEL_BEGIN

using EffectData = std::tuple < Effect*, std::string, std::string, UINT >;

template<typename T>
struct Light
{
	

	static int RegisterLight(const T& light)
	{
		m_Lights.push_back(light);
		UpdateBindEffect();

		return m_Id++;
	}

	static void UnregisterLight(int id)
	{
		for (auto& light : m_Lights)
		{
			if (lights.first == id)
			{
				m_Lights.erase(&light);
				UpdateBindEffect();
				return;
			}
		}
	}

	static void UpdateLight(int id, const T& light)
	{
		for (auto& light : m_Lights)
		{
			if (lights.first == id)
			{
				lights.second = light;
				UpdateBindEffect();

				return;
			}
		}
	}

	static void GetLights(std::vector<T>& lights)
	{
		for (auto& light : m_Lights)
		{
			lights.push_back(light.second);
		}
	}

	static void UpdateBindEffect()
	{
		for (auto effectData : m_EffectData)
		{
			int lightNum = min(m_Lights.size(), std::get<3>(effectData));

			std::get<0>(effectData)->
				SetGenericMember(std::get<2>(effectData),
				lightNum, sizeof(UINT));

			T* data = m_Lights.data();

			if (data != nullptr)
			{
				std::get<0>(effectData)->
					SetGenericMember(std::get<1>(effectData),
					*data, sizeof(T)*lightNum);
			}

			
		}
	}

	static void BindEffect(Effect* effect, const std::string& member, const std::string& numMember, UINT maxNum)
	{
		m_EffectData.push_back(std::make_tuple(effect, member, numMember, maxNum));
	}

private:
	static std::vector<T> m_Lights;
	static std::vector<EffectData> m_EffectData;
	static int m_Id;
};

template<typename T>
std::vector<T> Light<T>::m_Lights;

template<typename T>
std::vector<EffectData> Light<T>::m_EffectData;

template<typename T>
int Light<T>::m_Id = 0;



NS_EEL_END