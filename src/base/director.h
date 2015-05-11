#pragma once
#include <map>
#include "base/macro.h"
#include "utility/singleton.h"
#include "component/scene.h"
#include "base/event/mouseEvent.h"

NS_EEL_BEGIN

class Director : public Object, public Singleton<Director>
{
public:
	Director();
	~Director();

	void GameLoop();

	template<typename T, typename F>
	void RegisterEvent(EventType type, T* object, F memFunc);

	void UnregisterEvent(EventType type, Object* object);
	void UnregisterAllEvent(Object* object);
	void ExcuteEvent(EventType type, const Event& e);

private:
	SPTR<Scene> m_RunningScene = nullptr;

	using EventList = std::vector < UPTR<EventEntry> > ;
	using EventMap = std::map < EventType, EventList > ;

	EventMap m_EventMap;
};

template<typename T, typename F>
void eel::Director::RegisterEvent(EventType type, T* object, F memFunc)
{
	UPTR<EventTask<T, F>> task = std::make_unique(object, memFunc);

	m_EventMap[type].push_back(std::move(task));
}

NS_EEL_END