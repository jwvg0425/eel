#include "MyApplication.h"
#include "FirstScene.h"
#include "MovingCamera.h"
#include "boxLand.h"

void MyApplication::FinishLaunching()
{
	eel::Renderer::GetInstance()->
		SetScreenBackgroundColor(eel::Color4(0.6f, 0.8f, 0.3f, 1.0f));

	eel::Renderer::GetInstance()->
		SetScreenCamera(MovingCamera::Create(eel::Point3(0.0f, 20.0f, 30.0f), eel::Point3(0.0f, 0.0f, 0.0f), eel::Vector3(0.0f, 1.0f, 0.0f)));

	eel::Director::GetInstance()->
		RunWithScene(FirstScene::Create());

	ShowCursor(false);
	
	GBoxLand = new BoxLand(eel::Vector3(10.f, 10.f, 10.f));
}