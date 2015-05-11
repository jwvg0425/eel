#include "director.h"
#include "base/renderer.h"

USING_NS_EEL;

void Director::GameLoop()
{
	//TODO : Update

	Renderer::GetInstance()->Render(m_RunningScene);
}

Director::Director()
{

}

Director::~Director()
{

}

void eel::Director::RunWithScene(SPTR<Scene> scene)
{
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
