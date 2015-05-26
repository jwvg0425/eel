#pragma once
#include "base/event/event.h"
#include "math/vector.h"

NS_EEL_BEGIN

struct MousePickTriangleEvent : public Event
{
	MousePickTriangleEvent(int triangleIdx, float dist, Point3 mousePos);
	~MousePickTriangleEvent() override = default;

	MousePickTriangleEvent(MousePickTriangleEvent& rhs) = default;
	MousePickTriangleEvent& operator=(MousePickTriangleEvent& rhs) = default;

	Point2 m_MousePos;
	int m_TriangleIdx;
	float m_Distance;
};

NS_EEL_END