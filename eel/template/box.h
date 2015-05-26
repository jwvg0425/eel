#pragma once
#include "eel.h"

class Box : public eel::Model
{
public:
	Box(eel::Vector3 boxSize, int gridX, int gridY, int gridZ);
	~Box();
	CREATE_FUNC(Box);

	void OnPick(const eel::MousePickTriangleEvent& e);
	void Update(const eel::UpdateEvent& e);

private:
	eel::Vector2 m_BoxSize;
	int m_GridX;
	int m_GridY;
	int m_GridZ;
};

