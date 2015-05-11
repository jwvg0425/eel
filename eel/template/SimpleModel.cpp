#include "SimpleModel.h"

SimpleModel::SimpleModel(std::vector<eel::PosColor> vertex, std::vector<UINT> index)
	: Model(vertex, index)
{
	SetEffect(eel::Renderer::GetInstance()->GetEffect("SimpleColor"));

	SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*eel::Renderer::GetInstance()->GetCurrentCamera()->GetViewProjection());
	});
}
