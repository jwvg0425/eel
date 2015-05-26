﻿#include "firstScene.h"
#include "eel.h"
#include "grid.h"


FirstScene::FirstScene()
{
	eel::DirectionalLight testLight;

	testLight.m_Ambient = eel::Color4(0.2f);
	testLight.m_Diffuse = eel::Color4(0.7f);
	testLight.m_Specular = eel::Color4(0.5f);
	testLight.m_Direction = eel::Vector3(-0.4f);

	ShowCursor(false);

	eel::DirectionalLight::RegisterLight(testLight);
}
