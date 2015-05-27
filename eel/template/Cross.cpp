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
	eel::Point4 pos = camera->GetEyePos() + 1.0f*camera->GetLook();

	SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());
}
