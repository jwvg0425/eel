#pragma once
#include "eel.h"

class FirstScene : public eel::Scene, public eel::MakeCreate<FirstScene>
{
public:
	FirstScene();
	~FirstScene() override = default;

};