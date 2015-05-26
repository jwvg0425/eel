#pragma once
#include <map>
#include "base/macro.h"
#include "utility/singleton.h"
#include "component/scene.h"
#include "base/event/mouseEvent.h"
#include "base/event/UpdateEvent.h"
#include "base/timer.h"
#include "math/vector.h"

NS_EEL_BEGIN

class Director : public Object, public Singleton<Director>
{
public:
	Director();
	~Director();

	void GameLoop();

	void RunWithScene(SPTR<Scene> scene);
	template<typename T, typename E>
	void RegisterEvent(EventType type, T* object, void (T::*memFunc)(E));

	void UnregisterEvent(EventType type, Object* object);
	void UnregisterAllEvent(Object* object);
	void ExecuteEvent(EventType type, const Event& e);

	void UpdateMousePos(const MouseEvent& event);
	Point2	GetCurrentMousePos() const
	{
		return m_MousePos;
	}

	SPTR<Scene> GetRunningScene(){ return m_RunningScene; }

private:
	SPTR<Scene> m_RunningScene = nullptr;

	using EventList = std::vector < UPTR<EventEntry> > ;
	using EventMap = std::map < EventType, EventList > ;

	EventMap m_EventMap;
	Timer m_Timer;
	Point2 m_MousePos;
};

template<typename T, typename E>
void eel::Director::RegisterEvent(EventType type, T* object, void (T::*memFunc)(E))
{
	m_EventMap[type].push_back(std::make_unique<EventTask<T, decltype(memFunc), std::decay_t<E>>>(object, memFunc));
}

NS_EEL_END