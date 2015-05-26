#include "stdafx.h"
#include <Windows.h>
#include "observerApp.h"
#include "networkManager.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
					 , LPSTR lpszCmdParam, int nCmdShow)
{
	ObserverApp app;

	app.Init(L"dummy client", 800, 600);

	return app.Run();
}