#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	Object(Object& rhs) = default;
	Object& operator=(Object& rhs) = default;

private:
};

NS_EEL_END