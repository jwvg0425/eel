#include "MovingCamera.h"
#include "boxLand.h"

MovingCamera::MovingCamera(eel::Point3 eyePos, eel::Point3 targetPos, eel::Vector3 up)
	:PerspectiveCamera(eyePos, targetPos, up)
{
	eel::Director::GetInstance()->
		RegisterEvent(eel::EventType::UPDATE, this, &MovingCamera::Update);

	eel::Director::GetInstance()->
		RegisterEvent(eel::EventType::MOUSE_MOVE, this, &MovingCamera::MouseMove);
}

void MovingCamera::Update(const eel::UpdateEvent& e)
{
	if (eel::KeyManager::GetInstance()->IsKeyState(VK_W, eel::Key::PRESS))
	{
		Walk(10.0f*e.m_DTime);
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_S, eel::Key::PRESS))
	{
		Walk(-10.0f*e.m_DTime);
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_A, eel::Key::PRESS))
	{
		Strafe(-10.0f*e.m_DTime);
	}

	if (eel::KeyManager::GetInstance()->IsKeyState(VK_D, eel::Key::PRESS))
	{
		Strafe(10.0f*e.m_DTime);
	}

	float dy = m_Gravity*e.m_DTime;
	auto eyePos = GetEyePos();
	float currentY = eyePos.GetY();
	float nextY = currentY;
	float standardY = m_Height + GBoxLand->LowerLimit(eyePos);
	if(currentY - dy > standardY)
	{
		nextY = currentY - dy;
	}
	else
	{
		nextY = standardY;
	}
	eyePos.SetY(nextY);
	SetEyePos(eyePos);
}

void MovingCamera::MouseMove(const eel::MouseEvent& e)
{
	if (e.m_State & eel::MouseEvent::RIGHT)
	{

		float dx = XMConvertToRadians(0.25f*(e.m_Position.GetX()- m_LastPos.GetX()));
		float dy = XMConvertToRadians(0.25f*(e.m_Position.GetY() - m_LastPos.GetY()));

		if (!m_First)
		{
			Pitch(dy);
			RotateY(dx);
		}
	}

	m_LastPos = e.m_Position;
	m_First = false;
}
