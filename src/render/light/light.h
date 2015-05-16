#pragma once
#include "base/object.h"
#include "base/renderer.h"
#include <functional>
#include <string>
#include <vector>

NS_EEL_BEGIN

using BindEffectData = std::tuple < std::string, std::string, std::string >;

template<typename T>
struct Light
{
public:
	Light();
	static void BindEffect(const std::string& effectName, const std::string& lightName, const std::string& lightNumName);
	static const T& RegisterLight(const T& light);
	static void RemoveLight(const T& light);
	static void ClearLight();

	static void Update();

private:
	static std::vector<BindEffectData> m_Updates;
	static std::vector<T> m_Lights;
	static bool m_IsRegistered;
};

template<typename T>
Light<T>::Light()
{
	if (m_IsRegistered)
	{
		Renderer::GetInstance()->RegisterLightFunction(&Light<T>::ClearLight, &Light<T>::Update);
		m_IsRegistered = true;
	}
}

template<typename T>
void Light<T>::ClearLight()
{
	m_Lights.clear();
}

template<typename T>
void Light<T>::BindEffect(const std::string& effectName, const std::string& lightName, const std::string& lightNumName)
{
	m_Updates.push_back(BindEffectData(effectName, lightName, lightNumName));
}

template<typename T>
const T& Light<T>::RegisterLight(const T& light)
{
	m_Lights.push_back(light);

	return m_Lights[m_Lights.size() - 1];
}

template<typename T>
void Light<T>::RemoveLight(const T& light)
{
	m_Lights.erase(&light);
}


template<typename T>
void Light<T>::Update()
{
	for (auto& updater : m_Updates)
	{
		Renderer::GetInstance()->GetEffect(std::get<1>(updater))->SetGenericMember(std::get<2>(updater), m_Lights, sizeof(T)*m_Lights.size());
		Renderer::GetInstance()->GetEffect(std::get<1>(updater))->SetGenericMember(std::get<3>(updater), m_Lights.size(), sizeof(UINT));
	}
}

template<typename T>
std::vector<BindEffectData> Light<T>::m_Updates;

template<typename T>
std::vector<T> Light<T>::m_Lights;

template<typename T>
bool Light<T>::m_IsRegistered = false;

NS_EEL_END