#pragma once
#include "macro.h"

NS_EEL_BEGIN

class Application
{
public:
	Application();
	virtual ~Application();

	static Application* GetInstance();

	//be careful. 
	virtual LRESULT CALLBACK WndProc
		(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	int Run();

private:
	static Application* m_Instance;
};

NS_EEL_END