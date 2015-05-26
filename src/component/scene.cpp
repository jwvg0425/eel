#include"scene.h"
#include "base/renderer.h"


USING_NS_EEL;

void eel::Scene::Render() const
{
	for (auto& child : GetAllChilds())
	{
		if (!Renderer::GetInstance()->GetCurrentRenderTarget()->IsIgnore(child))
		{
			child->Render();
		}
	}
}

