#pragma once
#include "eel.h"

class MovingCamera : public eel::PerspectiveCamera
{
public:
	CREATE_FUNC(MovingCamera);

	MovingCamera(eel::Point3 eyePos, eel::Point3 targetPos, eel::Vector3 up);
	~MovingCamera() override = default;

	void Update(const eel::UpdateEvent& e);
	void MouseMove(const eel::MouseEvent& e);

private:
	bool		m_First = true;
	eel::Point2 m_LastPos;
	float		m_Height = 10.f;
	float		m_Gravity = 20.f;
};