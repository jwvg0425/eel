#pragma once
#include "eel.h"

#define WIDTH_BOX_NUM 10
#define HEIGHT_BOX_NUM 20
#define DEPTH_BOX_NUM 10
#define ZERO_HEIGHT -100.f

class BoxLand
{
public:
	BoxLand(eel::Vector3 boxSize);
	~BoxLand();

	void AddBox();
	void SetBoxState(eel::Vector3 position, bool state);
	eel::Vector3 GetRealPos(eel::Vector3 gridPos);
	eel::Vector3 GetGridPos(eel::Vector3 realPos);
	bool IsInTheLand(eel::Vector3 gridPos);
	float UpperLimit(eel::Vector3 realPos);
	float LowerLimit(eel::Vector3 realPos);
public:
	eel::Vector3 m_MousePosForCreate;
	eel::Vector3 m_MousePosForDestroy;
	eel::Vector3 m_GridOrigin;

	ARRAY3D<bool, WIDTH_BOX_NUM, HEIGHT_BOX_NUM, DEPTH_BOX_NUM> m_BoxStates;
	eel::Vector3 m_BoxSize;
};

extern BoxLand* GBoxLand;
