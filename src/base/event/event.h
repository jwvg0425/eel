#pragma once
#include <type_traits>
#include "base/macro.h"
#include "base/object.h"

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
	virtual Object* GetEventObject() = 0;
};

template<typename Obj, typename Func>
class EventTask : public EventEntry
{
public:
	EventTask(Obj* object, Func func)
	: m_Object(object), m_Function(func) 
	{
		static_assert(std::is_base_of(Object, Obj)::value, "Obj must inherit eel::Object");
	}
	virtual void Excute(const Event& e)
	{
		m_Object->(*m_Function)(e);
	}

	virtual Object* GetEventObject()
	{
		return m_Object;
	}

private:
	Obj* m_Object;
	Func m_Function;
};

NS_EEL_END