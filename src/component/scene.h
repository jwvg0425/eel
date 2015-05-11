#pragma once
#include "component/component.h"

NS_EEL_BEGIN
class Scene : public Component
{
public:
	Scene() = default;
	~Scene() override = default;

	virtual void Render() const;

private:
};

NS_EEL_END