#include "firstScene.h"
#include "utility\log.h"
#include "base\director.h"
#include "math\ray.h"

FirstScene::FirstScene()
{
	eel::DirectionalLight testLight;

	testLight.m_Ambient = eel::Color4(0.2f);
	testLight.m_Diffuse = eel::Color4(0.7f);
	testLight.m_Specular = eel::Color4(0.5f);
	testLight.m_Direction = eel::Vector3(-0.4f);

	eel::DirectionalLight::RegisterLight(testLight);

	std::vector<eel::PosBasic> vertex;
	std::vector<UINT> index;

	eel::MeshGenerator::CreateCube(2.0f, 2.0f, 2.0f, vertex, index);

	auto model = eel::Model::Create(vertex, index);

	eel::LightMaterial mat;

	mat.m_Ambient = eel::Color4(0.2f);
	mat.m_Diffuse = eel::Color4(0.7f,0.2f,0.2f,1.0f);
	mat.m_Specular = eel::Color4(0.5f,0.5f,0.5f,16.0f);

	model->AddMaterial("light", mat);
	model->AddShaderResource("texture", "resource/texture/WoodCrate01.dds");

	model->SetEffect(eel::Renderer::GetInstance()->GetEffect("Basic"));

	model->SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		auto camera = eel::Renderer::GetInstance()->GetCurrentCamera();
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*camera->GetViewProjection());
		effect->SetMatrixMember("gWorld", model->GetWorld());
		effect->SetMatrixMember("gWorldInvTranspose", eel::Math::InverseTranspose(model->GetWorld()));
		eel::MaterialData mat = model->GetMaterial(("light"));
		
		effect->SetGenericMember("gMaterial", mat.m_Material, mat.m_Size);
		effect->SetMatrixMember("gTexTransform", eel::Math::I);
		effect->SetResourceMember("gDiffuseMap", model->GetShaderResource("texture"));

		auto mousePos = eel::Director::GetInstance()->GetCurrentMousePos();
		if(int peekedIndex = model->CheckWithRay(camera->GetCameraRay()) != -1)
		{
			//using eel::DebugLogW;
			eel::LOG(L"%d번째 삼각형 Peeked\n", peekedIndex);
		}
	});

	AddChild(model);
}
