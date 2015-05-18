#include "firstScene.h"

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

	eel::Material mat;

	mat.m_Ambient = eel::Color4(0.2f);
	mat.m_Diffuse = eel::Color4(0.7f,0.2f,0.2f,1.0f);
	mat.m_Specular = eel::Color4(0.5f,0.5f,0.5f,16.0f);


	model->SetEffect(eel::Renderer::GetInstance()->GetEffect("SimpleLight"));

	model->SetRenderUpdate([mat](const eel::Model* model, eel::Effect* effect)
	{
		effect->SetMatrixMember("gWorldViewProj", model->GetWorld()*eel::Renderer::GetInstance()->GetCurrentCamera()->GetViewProjection());
		effect->SetMatrixMember("gWorld", model->GetWorld());
		effect->SetMatrixMember("gWorldInvTranspose", eel::Math::inverseTranspose(model->GetWorld()));
		effect->SetGenericMember("gMaterial", mat, sizeof(eel::Material));
		eel::Point3 eyePos = eel::Renderer::GetInstance()->GetCurrentCamera()->GetEyePos();
		effect->SetVectorMember("gEyePosW", eel::Vector4(eyePos.GetX(), eyePos.GetY(), eyePos.GetZ(), 1.0f));
		eel::DirectionalLight::UpdateBindEffect();
	});

	AddChild(model);
}
