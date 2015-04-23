#include <Windows.h>
#include "eel.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	eel::Application program;

	program.Init(L"dummy client", 800, 600);

	return program.Run();
}