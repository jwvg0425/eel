#include <string>
#include "object.h"


USING_NS_EEL;

void eel::Object::AddChild(SPTR<Object> child)
{
	AddChild(child, child->m_Name);
}

void eel::Object::AddChild(SPTR<Object> child, std::string name)
{
	std::hash<std::string> nameHash;

	child->m_Name = name;
	child->m_NameHash = nameHash(name);

	m_Childs.push_back(std::move(child));
}
