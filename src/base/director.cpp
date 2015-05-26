#include "director.h"
#include "base/renderer.h"
#include "base/keyManager.h"
#include "base/application.h"
#include "math/mathHelper.h"
#include "base/event/mousePickTriangleEvent.h"
#include <time.h>
#include <algorithm>

USING_NS_EEL;

void Director::GameLoop()
{
	m_Timer.Tick();
	Renderer::GetInstance()->Render(m_RunningScene);
	Director::ExecuteEvent(EventType::UPDATE, UpdateEvent(m_Timer.DeltaTime()));

	//pick event
	PickingCheck();
}

Director::Director()
{
	KeyManager::GetInstance();
	srand((unsigned)time(nullptr));
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

eel::Ray eel::Director::GetMouseRay()
{
	Matrix4 projection = Renderer::GetInstance()->GetScreenCamera()->GetProjection();

	float vx = (+2.0f*m_MousePos.GetX() / Application::GetInstance()->GetWidth() - 1.0f) / projection(0, 0);
	float vy = (-2.0f*m_MousePos.GetY() / Application::GetInstance()->GetHeight() + 1.0f) / projection(1, 1);

	Ray ray;

	Point4 origin(0.0f, 0.0f, 0.0f, 1.0f);
	Vector4 direction(vx, vy, 1.0f, 0.0f);

	Matrix4 view = Renderer::GetInstance()->GetScreenCamera()->GetView();
	Matrix4 invView = Math::Inverse(view);

	origin = XMVector3TransformCoord(origin, invView);
	direction = XMVector3TransformNormal(direction, invView);

	ray.SetRayOrigin(origin);
	ray.SetRayDirection(direction);

	return ray;
}

void eel::Director::PickingCheck()
{
	//mouse picking check(in running scene)
	Ray ray = GetMouseRay();
	float minDist = Math::INF;
	static WPTR<Component> prevChild;
	SPTR<Component> minChild = nullptr;

	int minPick = -1;
	for (auto child : m_RunningScene->GetAllChilds())
	{
		int pick = child->CheckWithRay(ray, minDist);

		if (pick != -1)
		{
			minPick = pick;
			minChild = child;
		}
	}

	auto prev = prevChild.lock();

	auto ExecuteRegisteredEvent = [this](SPTR<Component> minChild, const Event& e)
	{
		for(auto& entry : m_EventMap[EventType::MOUSE_PICK_TRIANGLE])
		{
			if (entry->GetEventObject() == minChild.get())
			{
				entry->Excute(e);
				return;
			}
		}
	};

	Vector3 pickPos = ray.GetRayOrigin() + ray.GetRayDirection() * minDist;

	if (prev != nullptr && prev != minChild)
	{
		MousePickTriangleEvent e(-1, minDist, pickPos);

		ExecuteRegisteredEvent(prev, e);
		e.m_TriangleIdx = minPick;
		ExecuteRegisteredEvent(minChild, e);

		WPTR<Component> weak(minChild);
		prevChild.swap(weak);
	}
}
