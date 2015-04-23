#pragma once
#include <memory>
#include "base/macro.h"


NS_EEL_BEGIN

template<typename T>
class MakeCreate
{
public:
	template<typename... Args>
	static std::shared_ptr<T> Create(Args&&... args)
	{
		auto ptr = std::make_shared<T>(std::forward<Args>(args)...);

		return ptr;
	}
};

NS_EEL_END