#include <Windows.h>

#include "application.h"
#include "director.h"

USING_NS_EEL;

Application* Application::m_Instance = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return Application::GetInstance()->WndProc(hWnd, iMessage, wParam, lParam);
}

eel::Application::Application()
{
	_ASSERT(m_Instance == nullptr);

	m_Instance = this;
}

eel::Application::~Application()
{
	m_Instance = nullptr;
}

Application* eel::Application::GetInstance()
{
	_ASSERT(m_Instance != nullptr);

	return m_Instance;
}

int eel::Application::Run()
{
	MSG message;

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			Director::GetInstance()->GameLoop();
		}
	}

	return 0;
}

bool eel::Application::MakeWindow(std::wstring title, int width, int height)
{
	m_Title = title;
	m_Width = static_cast<float>(width);
	m_Height = static_cast<float>(height);

	WNDCLASS WndClass;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = m_InstanceHandle;
	WndClass.lpfnWndProc = ::WndProc;
	WndClass.lpszClassName = L"EELApplication";
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	m_WindowHandle = CreateWindow(L"EELApplication", title.c_str(), 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, (HMENU)NULL, m_InstanceHandle, NULL);

	//TODO : store window size

	if (m_WindowHandle == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool eel::Application::Init(std::wstring title, int width, int height)
{
	m_InstanceHandle = GetModuleHandle(nullptr);

	if (!MakeWindow(title, width, height))
	{
		return false;
	}

	ShowWindow(m_WindowHandle, SW_SHOWNORMAL);

	return true;
}

LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
