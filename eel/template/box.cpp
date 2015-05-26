#include "box.h"
#include "boxLand.h"

Box::Box(eel::Vector3 boxSize, int gridX, int gridY, int gridZ) :
m_GridX(gridX), m_GridY(gridY), m_GridZ(gridZ)
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

	eel::Director::GetInstance()->RegisterEvent(eel::EventType::MOUSE_PICK_TRIANGLE, this, &Box::OnPick);
	eel::Director::GetInstance()->RegisterEvent(eel::EventType::UPDATE, this, &Box::Update);
}


Box::~Box()
{
}

void Box::OnPick(const eel::MousePickTriangleEvent& e)
{
	int triangle = e.m_TriangleIdx;
	
	if (triangle == -1)
	{
		GBoxLand->m_MousePosForDestroy = eel::Vector3(-1, -1, -1);
		GBoxLand->m_MousePosForCreate = eel::Vector3(-1, -1, -1);
		return;
	}

	int i1 = GetMesh()->GetIndex(triangle * 3 + 0);
	int i2 = GetMesh()->GetIndex(triangle * 3 + 1);
	int i3 = GetMesh()->GetIndex(triangle * 3 + 2);

	auto v1 = GetMesh()->GetPosByIndex(i1);
	auto v2 = GetMesh()->GetPosByIndex(i2);
	auto v3 = GetMesh()->GetPosByIndex(i3);

	eel::Vector3 a1 = *v2 - *v1;
	eel::Vector3 a2 = *v3 - *v1;
	eel::Vector3 cross = a1.Cross(a2);

	cross = cross.Normalize();

	eel::LOG(L"%f %f %f", cross.GetX(), cross.GetY(), cross.GetZ());

	GBoxLand->m_MousePosForDestroy = eel::Vector3(m_GridX, m_GridY, m_GridZ);
	GBoxLand->m_MousePosForCreate = eel::Vector3(m_GridX + cross.GetX(), m_GridY + cross.GetY(), m_GridZ + cross.GetZ());
}

void Box::Update(const eel::UpdateEvent& e)
{
	if (!GBoxLand->m_BoxStates[m_GridX][m_GridY][m_GridZ])
	{
		RemoveFromParent();
		return;
	}
}
