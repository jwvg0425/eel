#pragma once
#include "base/object.h"
#include "math/ray.h"

NS_EEL_BEGIN

class Component : public Object
{
public:
	using ChildList = std::vector<SPTR<Component> >;

	Component() = default;
	~Component() override = default;

	Component(Component& rhs) = delete;
	Component& operator=(Component& rhs) = delete;


	template<typename T>
	void AddChild(UPTR<T>& child)
	{
		SPTR<Component> sharedChild = std::move(child);
		AddChild(sharedChild, sharedChild->m_Name);
	}

	template<typename T>
	void Addchild(UPTR<T>& child, const std::string& name)
	{
		SPTR<Component> sharedChild = std::move(child);
		AddChild(sharedChild, name);
	}

	void AddChild(SPTR<Component> child);
	void AddChild(SPTR<Component> child, const std::string& name);

	SPTR<Component> GetChildByName(const std::string& name);

	bool RemoveChild(SPTR<Component> child);
	bool RemoveChildByName(const std::string& name);

	void RemoveAllChilds();

	const ChildList& GetAllChilds() const;

	virtual void Render() const = 0;

	virtual int CheckWithRay(const Ray& ray) const;
	virtual int CheckWithRay(const Ray& ray, OUT float& minDist) const;

private:

	ChildList m_Childs;

	//parent ptr -> weak ptr
	Component* m_Parent = nullptr;

	//identifier
	std::string m_Name = "";
	std::size_t m_NameHash = 0; // speed up 
};

NS_EEL_END