#include "MyApplication.h"
#include "FirstScene.h"

void MyApplication::FinishLaunching()
{
	eel::Renderer::GetInstance()->
		SetScreenBackgroundColor(eel::Color4(0.6f, 0.3f, 0.3f, 1.0f));

	eel::Renderer::GetInstance()->
		SetScreenCamera(eel::PerspectiveCamera::Create(eel::Point3(0.0f, 20.0f, 30.0f), eel::Point3(0.0f, 0.0f, 0.0f), eel::Vector3(0.0f, 1.0f, 0.0f)));

	eel::Director::GetInstance()->
		RunWithScene(FirstScene::Create());
}
