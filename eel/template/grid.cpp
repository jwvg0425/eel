#include "grid.h"
#include <vector>

Grid::Grid(float width, float depth, int widthBoxNum, int depthBoxNum)
{
	InitGrid(width, depth, widthBoxNum, depthBoxNum);
}

Grid::Grid(eel::Vector2 boxSize, int widthBoxNum, int depthBoxNum)
{
	float width = boxSize.GetX() * widthBoxNum;
	float depth = boxSize.GetY() * depthBoxNum;
	InitGrid(width, depth, widthBoxNum, depthBoxNum);
}


Grid::~Grid()
{

}

void Grid::InitGrid(float width, float depth, int widthBoxNum, int depthBoxNum)
{
	std::vector<eel::PosBasic> vertices;
	std::vector<UINT> indices;
	eel::MeshGenerator::CreateGrid(width, depth, widthBoxNum, depthBoxNum, vertices, indices);
	InitMesh(vertices, indices);
	SetEffect(eel::Renderer::GetInstance()->GetEffect("Basic"));

	eel::LightMaterial mat;
	mat.m_Ambient = eel::Color4(0.2f);
	mat.m_Diffuse = eel::Color4(0.7f, 0.7f, 0.7f, 1.0f);
	mat.m_Specular = eel::Color4(0.5f, 0.5f, 0.5f, 16.0f);

	AddMaterial("light", mat);
	SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		auto camera = eel::Renderer::GetInstance()->GetCurrentCamera();
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*camera->GetViewProjection());
		effect->SetMatrixMember("gWorld", model->GetWorld());
		effect->SetMatrixMember("gWorldInvTranspose", eel::Math::InverseTranspose(model->GetWorld()));
		eel::MaterialData mat = model->GetMaterial(( "light" ));

		effect->SetGenericMember("gMaterial", mat.m_Material, mat.m_Size);
		effect->SetMatrixMember("gTexTransform", eel::Math::I);
		effect->SetResourceMember("gDiffuseMap", eel::ShaderResource("resource/texture/Grass.dds"));
	});

}
