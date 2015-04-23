#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (m_Instance == nullptr)
		{
			m_Instance = new T;
		}

		return m_Instance;
	}
	
	static void ReleaseInstance()
	{
		SAFE_DELETE(m_Instance);
	}

	Singleton() = default;
	~Singleton() = default;

	Singleton(Singleton& rhs) = delete;
	Singleton& operator=(Singleton& rhs) = delete;

private:
	static T* m_Instance;
};

template<typename T>
T* Singleton<T>::m_Instance = nullptr;

NS_EEL_END