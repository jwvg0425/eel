#pragma once
#include "eel.h"

class Box : public eel::Model
{
public:
	Box(eel::Vector3 boxSize);
	~Box();
	CREATE_FUNC(Box);

private:
	eel::Vector2 m_BoxSize;
	int m_GridX;
	int m_GridY;
	int m_GridZ;
};

