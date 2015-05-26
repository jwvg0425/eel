#pragma once
#include "eel.h"


class Grid : public eel::Model
{
public:
	Grid();
	Grid(float width, float depth, int widthBoxNum, int depthBoxNum);
	Grid(eel::Vector2 boxSize, int widthBoxNum, int depthBoxNum);
	~Grid();

	CREATE_FUNC(Grid);

	void InitGrid(float width, float depth, int widthBoxNum, int depthBoxNum);
};

