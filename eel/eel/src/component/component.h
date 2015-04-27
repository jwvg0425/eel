#pragma once
#include "base/object.h"
#include "math/vector.h"

NS_EEL_BEGIN

class Component : public Object
{
public:
	Component() = default;
	~Component() override = default;

	Component(Component& rhs) = delete;
	Component& operator=(Component& rhs) = delete;

	void AddChild(SPTR<Component> child);
	void AddChild(SPTR<Component> child, const std::string& name);

	SPTR<Component> GetChildByName(const std::string& name);

	bool RemoveChild(SPTR<Component> child);
	bool RemoveChildByName(const std::string& name);

	void RemoveAllChilds();

private:
	using ChildList = std::vector<SPTR<Component> >;

	ChildList m_Childs;

	//parent ptr -> weak ptr
	Component* m_Parent = nullptr;

	//identifier
	std::string m_Name = "";
	std::size_t m_NameHash = 0; // speed up 

	Vector		m_Position;
};

NS_EEL_END