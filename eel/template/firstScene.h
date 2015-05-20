#pragma once
#include "eel.h"

class FirstScene : public eel::Scene
{
public:
	CREATE_FUNC(FirstScene);

	FirstScene();
	~FirstScene() override = default;

};