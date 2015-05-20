#include <Windows.h>
#include "eel.h"
#include "myApplication.h"
#include "firstScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	MyApplication program;

	program.Init(L"dummy client", 800, 600);

	return program.Run();
}