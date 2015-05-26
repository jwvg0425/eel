#pragma once

class MovingCamera : public eel::PerspectiveCamera
{
public:
	MovingCamera(eel::Point3 eyePos, eel::Point3 targetPos, eel::Vector3 up);
	~MovingCamera() override = default;

	void Update(const eel::UpdateEvent& e);
	void MouseMove(const eel::MouseEvent& e);

	CREATE_FUNC(MovingCamera);

private:
	bool		m_First = true;
	eel::Point2 m_LastPos;
};