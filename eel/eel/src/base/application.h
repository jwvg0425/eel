#pragma once
#include <Windows.h>
#include <string>
#include "macro.h"

NS_EEL_BEGIN

class Application
{
public:
	Application();
	virtual ~Application();

	static Application* GetInstance();

	//be careful. DON'T override unless you know what you are doing.
	virtual LRESULT CALLBACK WndProc
		(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	int Run();

	bool Init(std::wstring title, int width, int height);

private:
	bool MakeWindow(std::wstring title, int width, int height);

	READ_ONLY(std::wstring, Title);

	READ_ONLY(HWND, WindowHandle);
	READ_ONLY(HINSTANCE, InstanceHandle);

	static Application* m_Instance;
};

NS_EEL_END