#pragma once
#include "eel.h"

class SimpleModel : public eel::Model, public eel::MakeCreate<SimpleModel>
{
public:
	SimpleModel(std::vector<eel::PosColor> vertex, std::vector<UINT> index);
	~SimpleModel() override = default;

private:
};