#pragma once
#include "eel.h"

class BoxLand
{
public:
	BoxLand(eel::Vector3 boxSize, int widthBoxNum, int heightBoxNum, int depthBoxNum);
	~BoxLand();

private:
	eel::Vector3 m_BoxSize;
	eel::Vector3 m_GridOrigin;
	int m_MaxXIdx;
	int m_MaxYIdx;
	int m_MaxZIdx;
};

extern BoxLand* GBoxLand;
