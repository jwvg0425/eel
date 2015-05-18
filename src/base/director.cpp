#include "director.h"
#include "base/renderer.h"
#include "base/keyManager.h"

USING_NS_EEL;

void Director::GameLoop()
{
	m_Timer.Tick();
	Director::ExecuteEvent(EventType::UPDATE, UpdateEvent(m_Timer.DeltaTime()));

	Renderer::GetInstance()->Render(m_RunningScene);
}

Director::Director()
{
	KeyManager::GetInstance();
	m_Timer.Reset();
	RegisterEvent(EventType::MOUSE_MOVE, this, &eel::Director::UpdateMousePos);
}

Director::~Director()
{

}

void eel::Director::RunWithScene(SPTR<Scene> scene)
{
	_ASSERT(m_RunningScene == nullptr);

	m_RunningScene = scene;
}

void eel::Director::ExecuteEvent(EventType type, const Event& e)
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

void eel::Director::UpdateMousePos(const MouseEvent& event)
{
	m_MousePos = event.m_Position;
}
