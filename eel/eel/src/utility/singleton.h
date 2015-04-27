#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

template<typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		static T instance;

		return &instance;
	}

	Singleton(Singleton& rhs) = delete;
	Singleton& operator=(Singleton& rhs) = delete;

protected:
	Singleton() {}
	~Singleton() {}

};

NS_EEL_END