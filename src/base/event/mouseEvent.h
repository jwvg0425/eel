#pragma once
#include "base/event/event.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct MouseEvent : public Event
{
	enum State
	{
		NONE = 0x0,
		LEFT = 0x1,
		RIGHT = 0x2
	};

	MouseEvent(Point2 position, int state);
	~MouseEvent() override = default;

	MouseEvent(MouseEvent& rhs) = default;
	MouseEvent& operator=(MouseEvent& rhs) = default;

	Point2 m_Position;
	int m_State;
};

NS_EEL_END