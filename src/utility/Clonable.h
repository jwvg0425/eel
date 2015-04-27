#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

template <typename T>
class Clonable
{
public:
	virtual T* Clone() const = 0;

	Clonable() = default;
	~Clonable() = default;

	Clonable(Clonable& rhs) = delete;
	Clonable& operator=(Clonable& rhs) = delete;
};

NS_EEL_END