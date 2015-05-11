#include <Windows.h>
#include "eel.h"
#include "firstScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	eel::Application program;

	program.Init(L"dummy client", 800, 600);

	eel::Renderer::GetInstance()->
		SetScreenBackgroundColor(eel::Color4(0.6f, 0.3f, 0.3f, 1.0f));

	eel::Renderer::GetInstance()->
		SetScreenCamera(new eel::PerspectiveCamera(eel::Point3(0.0f, 20.0f, 30.0f), eel::Point3(0.0f, 0.0f, 0.0f), eel::Vector3(0.0f, 1.0f, 0.0f)));

	eel::Director::GetInstance()->
		RunWithScene(FirstScene::Create());

	return program.Run();
}