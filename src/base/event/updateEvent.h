#pragma once
#include "base/event/event.h"

NS_EEL_BEGIN

struct UpdateEvent : public Event
{
	UpdateEvent(float dTime);
	~UpdateEvent() override = default;

	UpdateEvent(UpdateEvent& rhs) = default;
	UpdateEvent& operator=(UpdateEvent& rhs) = default;

	float m_DTime;
};

NS_EEL_END