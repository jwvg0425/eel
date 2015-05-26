#include "box.h"

Box::Box(eel::Vector3 boxSize)
{
	std::vector<eel::PosBasic> vertex;
	std::vector<UINT> index;

	eel::MeshGenerator::CreateCube(boxSize.GetX(), boxSize.GetY(), boxSize.GetZ(), vertex, index);

	InitMesh(vertex, index);

	eel::LightMaterial mat;

	mat.m_Ambient = eel::Color4(0.2f);
	mat.m_Diffuse = eel::Color4(0.7f, 0.7f, 0.7f, 1.0f);
	mat.m_Specular = eel::Color4(0.5f, 0.5f, 0.5f, 16.0f);

	AddMaterial("light", mat);
	AddShaderResource("texture", "resource/texture/WoodCrate01.dds");

	SetEffect(eel::Renderer::GetInstance()->GetEffect("Basic"));
	SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		auto camera = eel::Renderer::GetInstance()->GetCurrentCamera();
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*camera->GetViewProjection());
		effect->SetMatrixMember("gWorld", model->GetWorld());
		effect->SetMatrixMember("gWorldInvTranspose", eel::Math::InverseTranspose(model->GetWorld()));
		eel::MaterialData mat = model->GetMaterial(( "light" ));

		effect->SetGenericMember("gMaterial", mat.m_Material, mat.m_Size);
		effect->SetMatrixMember("gTexTransform", eel::Math::I);
		effect->SetResourceMember("gDiffuseMap", model->GetShaderResource("texture"));
	});
}


Box::~Box()
{
}
