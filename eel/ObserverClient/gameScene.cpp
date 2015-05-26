#include "stdafx.h"
#include "gameScene.h"

GameScene::GameScene()
{
	eel::DirectionalLight testLight;

	testLight.m_Ambient = eel::Color4(0.2f);
	testLight.m_Diffuse = eel::Color4(0.7f);
	testLight.m_Specular = eel::Color4(0.5f);
	testLight.m_Direction = eel::Vector3(-0.4f);

	eel::DirectionalLight::RegisterLight(testLight);
}
