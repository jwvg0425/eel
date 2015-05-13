#include "director.h"
#include "base/renderer.h"

USING_NS_EEL;

void Director::GameLoop()
{
	m_Timer.Tick();
	Director::ExcuteEvent(EventType::UPDATE, UpdateEvent(m_Timer.DeltaTime()));

	Renderer::GetInstance()->Render(m_RunningScene);
}

Director::Director()
{
	m_Timer.Reset();
}

Director::~Director()
{

}

void eel::Director::RunWithScene(SPTR<Scene> scene)
{
	_ASSERT(m_RunningScene == nullptr);

	m_RunningScene = scene;
}

void eel::Director::ExcuteEvent(EventType type, const Event& e)
{
	for (auto& task : m_EventMap[type])
	{
		task->Excute(e);
	}
}

void eel::Director::UnregisterEvent(EventType type, Object* object)
{
	for (auto it = m_EventMap[type].cbegin(); it != m_EventMap[type].cend();)
	{
		if ((*it)->GetEventObject() == object)
		{
			it = m_EventMap[type].erase(it);
		}
		else
		{
			++it;
		}
	}
}

void eel::Director::UnregisterAllEvent(Object* object)
{
	if (m_EventMap.size() == 0)
		return;

	for (auto& eventList : m_EventMap)
	{
		UnregisterEvent(eventList.first, object);
	}
}
