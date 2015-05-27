#include "cross.h"

Cross::Cross()
{
	std::vector<eel::PosColor> vertex;
	std::vector<UINT> index = { 0, 1, 2, 3 };

	vertex.push_back(eel::PosColor(0.0f, -0.1f, 0.0f, 1.0f, 1.0f, 1.0f,1.0f));
	vertex.push_back(eel::PosColor(0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertex.push_back(eel::PosColor(-0.1f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertex.push_back(eel::PosColor(0.1f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f));

	InitMesh(vertex, index);

	SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	SetEffect(eel::Renderer::GetInstance()->GetEffect("SimpleColor"));
	SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		auto camera = eel::Renderer::GetInstance()->GetCurrentCamera();
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*camera->GetViewProjection());

	});

	eel::Director::GetInstance()->RegisterEvent(eel::EventType::UPDATE, this, &Cross::Update);
}

void Cross::Update(const eel::UpdateEvent& e)
{
	auto camera = eel::Renderer::GetInstance()->GetScreenCamera();
	eel::Point3 eye = camera->GetEyePos();
	eel::Vector3 look = camera->GetLook();
	eel::Vector3 up = camera->GetUp();
	eel::Vector3 right = camera->GetRight();
	eel::Point3 center = eye + look*3.0f;

	std::vector<eel::PosColor> vertex;
	std::vector<UINT> index = { 0, 1, 2, 3 };

	vertex.push_back(eel::PosColor(center.GetX() - up.GetX() * 0.05f, center.GetY() - up.GetY() * 0.05f, center.GetZ() - up.GetZ() * 0.05f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertex.push_back(eel::PosColor(center.GetX() + up.GetX() * 0.05f, center.GetY() + up.GetY() * 0.05f, center.GetZ() + up.GetZ() * 0.05f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertex.push_back(eel::PosColor(center.GetX() - right.GetX() * 0.05f, center.GetY() - right.GetY() * 0.05f, center.GetZ() - right.GetZ() * 0.05f, 1.0f, 1.0f, 1.0f, 1.0f));
	vertex.push_back(eel::PosColor(center.GetX() + right.GetX() * 0.05f, center.GetY() + right.GetY() * 0.05f, center.GetZ() + right.GetZ() * 0.05f, 1.0f, 1.0f, 1.0f, 1.0f));

	InitMesh(vertex, index);
}
