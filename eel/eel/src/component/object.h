#pragma once
#include <vector>
#include "base/macro.h"

NS_EEL_BEGIN

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	Object(Object& rhs) = delete;
	Object& operator=(Object& rhs) = delete;

	void AddChild(SPTR<Object> child);
	void AddChild(SPTR<Object> child, std::string name);

private:
	using ChildList = std::vector<SPTR<Object> >;

	ChildList m_Childs;

	//identifier
	std::string m_Name = "";
	std::size_t m_NameHash = 0; // speed up 
};

NS_EEL_END