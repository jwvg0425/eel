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

	Director::ReleaseInstance();

	return 0;
}

bool eel::Application::MakeWindow(WCHAR* title, int width, int height)
{
	return true;
}
