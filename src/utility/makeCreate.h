﻿#pragma once
#include <memory>
#include "base/macro.h"


NS_EEL_BEGIN

template<typename T>
class MakeCreate
{
public:
	template<typename... Args>
	static UPTR<T> Create(Args&&... args)
	{
		auto ptr = std::make_unique<T>(std::forward<Args>(args)...);

		return ptr;
	}

	MakeCreate() = default;
	~MakeCreate() = default;
	MakeCreate(MakeCreate& rhs) = default;
	MakeCreate& operator=(MakeCreate& rhs) = default;
};

NS_EEL_END