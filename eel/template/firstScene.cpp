#include "firstScene.h"
#include "utility\log.h"
#include "base\director.h"
#include "math\ray.h"

FirstScene::FirstScene()
{
	std::vector<eel::PosNormal> vertex;
	std::vector<UINT> index;

	vertex.push_back(eel::PosNormal(eel::Point3(-0.25f, -0.25f, 0.25f), eel::Vector3(0.2f, 0.5f, 0.3f)));
	vertex.push_back(eel::PosNormal(eel::Point3(0.25f, 0.25f, 0.25f), eel::Vector3(0.7f, 0.3f, 0.1f)));
	vertex.push_back(eel::PosNormal(eel::Point3(-0.25f, 0.25f, 0.25f), eel::Vector3(0.1f, 0.6f, 0.8f)));

	index.push_back(0);
	index.push_back(1);
	index.push_back(2);

	eel::DirectionalLight testLight;

	testLight.m_Ambient = eel::Color4(0.2f);
	testLight.m_Diffuse = eel::Color4(0.7f);
	testLight.m_Specular = eel::Color4(0.5f);
	testLight.m_Direction = eel::Vector3(-0.4f);

	eel::DirectionalLight::RegisterLight(testLight);
	

	auto model = eel::Model::Create(vertex, index);

	eel::LightMaterial mat;

	mat.m_Ambient = eel::Color4(0.2f);
	mat.m_Diffuse = eel::Color4(0.7f,0.2f,0.2f,1.0f);
	mat.m_Specular = eel::Color4(0.5f,0.5f,0.5f,16.0f);

	model->AddMaterial("light", mat);


	model->SetEffect(eel::Renderer::GetInstance()->GetEffect("SimpleLight"));

	model->SetRenderUpdate([](const eel::Model* model, eel::Effect* effect)
	{
		auto camera = eel::Renderer::GetInstance()->GetCurrentCamera();
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*camera->GetViewProjection());
		effect->SetMatrixMember("gWorld", model->GetWorld());
		effect->SetMatrixMember("gWorldInvTranspose", eel::Math::InverseTranspose(model->GetWorld()));
		eel::MaterialData mat = model->GetMaterial(("light"));
		
		effect->SetGenericMember("gMaterial", mat.m_Material, mat.m_Size);

		auto mousePos = eel::Director::GetInstance()->GetCurrentMousePos();
		if(int peekedIndex = model->CheckWithRay(camera->GetCameraRay()) != -1)
		{
			//using eel::DebugLogW;
			eel::LOG(L"%d번째 삼각형 Peeked\n", peekedIndex);
		}
	});

	AddChild(model);
}
