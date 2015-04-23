#pragma once
#include <map>
#include "base/macro.h"

NS_EEL_BEGIN

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	Object(Object& rhs) = delete;
	Object& operator=(Object& rhs) = delete;

private:
	using ChildList = std::map<std::string, SPTR<Object> >;

	ChildList m_Childs;
};

NS_EEL_END