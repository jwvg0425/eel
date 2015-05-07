#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

enum class EventType
{
	NONE,
	MOUSE_MOVE,
	MOUSE_DOWN,
	MOUSE_UP,
	UPDATE,
};

struct Event
{
	Event() = default;
	virtual ~Event() = default;

	Event(Event& rhs) = default;
	Event& operator=(Event& rhs) = default;
};

class EventEntry
{
public:
	virtual void Excute(const Event& e) = 0;
};

template<typename Obj, typename Func>
class EventTask : public EventEntry
{
public:
	EventTask(Obj* object, Func func)
	: m_Object(object), m_Function(func) { }
	virtual void Excute(const Event& e);
private:
	Obj* m_Object;
	Func m_Function;
};

template<typename Obj, typename Func>
void eel::EventTask<Obj, Func>::Excute(const Event& e)
{
	m_Object->(*m_Function)(e);
}

NS_EEL_END