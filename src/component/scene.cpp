#include"scene.h"


USING_NS_EEL;

void eel::Scene::Render() const
{
	for (auto& child : GetAllChilds())
	{
		child->Render();
	}
}

