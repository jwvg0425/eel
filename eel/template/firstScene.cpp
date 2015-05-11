#include "firstScene.h"
#include "simpleModel.h"

FirstScene::FirstScene()
{
	std::vector<eel::PosColor> vertex;
	std::vector<UINT> index;

	vertex.push_back(eel::PosColor(eel::Point3(0.0f, 0.0f, 0.0f), eel::Color4(0.2f, 0.5f, 0.3f, 1.0f)));
	vertex.push_back(eel::PosColor(eel::Point3(0.0f, 1.5f, 0.0f), eel::Color4(0.1f, 0.6f, 0.8f, 1.0f)));
	vertex.push_back(eel::PosColor(eel::Point3(1.0f, 0.0f, 1.0f), eel::Color4(0.7f, 0.3f, 0.1f, 1.0f)));

	index.push_back(2);
	index.push_back(1);
	index.push_back(0);

	SPTR<SimpleModel> model = SimpleModel::Create(vertex, index);

	AddChild(model);
}
