#include "MovingCamera.h"
#include "boxLand.h"

MovingCamera::MovingCamera(eel::Point3 eyePos, eel::Point3 targetPos, eel::Vector3 up)
	:PerspectiveCamera(eyePos, targetPos, up)
{
	eel::Director::GetInstance()->
		RegisterEvent(eel::EventType::UPDATE, this, &MovingCamera::Update);

	eel::Director::GetInstance()->
		RegisterEvent(eel::EventType::MOUSE_DOWN, this, &MovingCamera::MouseDown);
}

void MovingCamera::Update(const eel::UpdateEvent& e)
{
	eel::Vector3 nextPos = GetEyePos();

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_W, eel::Key::PRESS))
	{
		eel::Vector3 go(GetLook().GetX(), 0.0f, GetLook().GetZ());
		eel::Vector3 s(10.0f*e.m_DTime);

		go = go.Normalize();

		nextPos = s.MultiplyAdd(go, GetEyePos());

		UpdateView();
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_S, eel::Key::PRESS))
	{
		eel::Vector3 go(GetLook().GetX(), 0.0f, GetLook().GetZ());
		eel::Vector3 s(-10.0f*e.m_DTime);


		go = go.Normalize();

		nextPos = s.MultiplyAdd(go, GetEyePos());

		UpdateView();
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_A, eel::Key::PRESS))
	{
		eel::Vector3 go(GetRight().GetX(), 0.0f, GetRight().GetZ());
		eel::Vector3 s(-10.0f*e.m_DTime);

		go = go.Normalize();

		nextPos = s.MultiplyAdd(go, GetEyePos());

		UpdateView();
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_D, eel::Key::PRESS))
	{
		eel::Vector3 go(GetRight().GetX(), 0.0f, GetRight().GetZ());
		eel::Vector3 s(10.0f*e.m_DTime);

		go = go.Normalize();

		nextPos = s.MultiplyAdd(go, GetEyePos());

		UpdateView();
	}
	auto grid = GBoxLand->GetGridPos(nextPos);
	int gridX = grid.GetX();
	int gridY = grid.GetY();
	int gridZ = grid.GetZ();

	if (!GBoxLand->m_BoxStates[gridX][gridY][gridZ])
	{
		SetEyePos(nextPos);
	}
	

	m_Speed -= m_Gravity*e.m_DTime;
	auto eyePos = GetEyePos();
	float currentY = eyePos.GetY();
	float nextY = currentY;
	float lowY = m_Height + GBoxLand->LowerLimit(eyePos);
	float highY = m_Height + GBoxLand->UpperLimit(eyePos);
	float dy = m_Speed * e.m_DTime;

	if(currentY + dy < lowY)
	{
		nextY = lowY;
		m_Speed = 0.0f;
		
		if (eel::KeyManager::GetInstance()->IsKeyState(VK_SPACE, eel::Key::PRESS))
		{
			m_Speed = 50.0f;
		}
	}
	else if (currentY + dy > highY)
	{
		nextY = highY;
		m_Speed = 0.0f;
	}
	else
	{
		nextY = currentY + dy;
	}

	eyePos.SetY(nextY);
	SetEyePos(eyePos);
	
	int width = eel::Application::GetInstance()->GetWidth();
	int height = eel::Application::GetInstance()->GetHeight();
	POINT mouse;

	GetCursorPos(&mouse);
	ScreenToClient(eel::Application::GetInstance()->GetWindowHandle(), &mouse);

	if (mouse.x != width / 2 &&
		mouse.y != height / 2)
	{

		float dx = XMConvertToRadians(0.25f*(mouse.x - width / 2));
		float dy = XMConvertToRadians(0.25f*(mouse.y - height / 2));

		if (!m_First)
		{
			Pitch(dy);
			RotateY(dx);
		}


		POINT p = { width / 2, height / 2 };

		ClientToScreen(eel::Application::GetInstance()->GetWindowHandle(), &p);

		SetCursorPos(p.x, p.y);
		m_First = false;
	}
}

void MovingCamera::MouseDown(const eel::MouseEvent& e)
{
	if (e.m_State & eel::MouseEvent::LEFT)
	{
		GBoxLand->AddBox();
	}
	else if (e.m_State & eel::MouseEvent::RIGHT)
	{
		auto pos = GBoxLand->m_MousePosForDestroy;
		int x = pos.GetX();
		int y = pos.GetY();
		int z = pos.GetZ();

		GBoxLand->m_BoxStates[x][y][z] = false;
	}
}
