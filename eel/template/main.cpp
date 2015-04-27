#include <Windows.h>
#include "eel.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	eel::Application program;

	program.Init(L"dummy client", 800, 600);

	eel::Renderer::GetInstance()->
		SetBackgroundColor(eel::Color(0.6f, 0.3f, 0.3f, 1.0f));

	return program.Run();
}