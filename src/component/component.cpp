#include "component.h"

USING_NS_EEL;

void eel::Component::AddChild(SPTR<Component> child)
{
	AddChild(child, child->m_Name);
}

void eel::Component::AddChild(SPTR<Component> child, const std::string& name)
{
	if (child == nullptr)
		return;

	std::hash<std::string> nameHash;

	child->m_Name = name;
	child->m_NameHash = nameHash(name);
	child->m_Parent = this;

	m_Childs.push_back(std::move(child));
	
}

SPTR<Component> eel::Component::GetChildByName(const std::string& name)
{
	std::hash<std::string> nameHash;
	std::size_t val = nameHash(name);

	for (auto& child : m_Childs)
	{
		//string compare is slow.
		//finding speed increased by using hash value.
		if (child->m_NameHash == val &&
			child->m_Name == name)
		{
			return child;
		}
	}

	return nullptr;
}

bool eel::Component::RemoveChild(SPTR<Component> child)
{
	for (auto it = m_Childs.cbegin(); it != m_Childs.cend();++it)
	{
		if (*it == child)
		{
			m_Childs.erase(it);
			return true;
		}
	}

	return false;
}

bool eel::Component::RemoveChildByName(const std::string& name)
{
	std::hash<std::string> nameHash;
	std::size_t val = nameHash(name);

	for (auto it = m_Childs.cbegin(); it != m_Childs.cend(); ++it)
	{
		auto& child = *it;
		
		//string compare is slow.
		//finding speed increased by using hash value.
		if (child->m_NameHash == val &&
			child->m_Name == name)
		{
			m_Childs.erase(it);
			return true;
		}
	}

	return false;
}

void eel::Component::RemoveAllChilds()
{
	m_Childs.clear();
}

const Component::ChildList& eel::Component::GetAllChilds() const
{
	return m_Childs;
}

int eel::Component::CheckWithRay(const Ray& ray) const
{
	return -1;
}

int eel::Component::CheckWithRay(const Ray& ray, OUT float& minDist) const
{
	return -1;
}

void eel::Component::RemoveFromParent()
{
	for (auto it = m_Parent->m_Childs.cbegin(); it != m_Parent->m_Childs.cend(); ++it)
	{
		if (it->get() == this)
		{
			m_Parent->m_Childs.erase(it);
			return;
		}
	}
}
