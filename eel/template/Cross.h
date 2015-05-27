#pragma once
#include "eel.h"

class Cross : public eel::Model
{
public:
	Cross();
	~Cross() override = default;

	void Update(const eel::UpdateEvent& e);

	CREATE_FUNC(Cross);
};