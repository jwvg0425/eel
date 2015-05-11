#pragma once
#include <Windows.h>
#include <string>
#include "base/macro.h"
#include "base/object.h"
#include "base/event/mouseEvent.h"

NS_EEL_BEGIN

class Application : public Object
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

	float GetAspectRatio() const;

private:
	void OnMouse(int x, int y, int state, EventType type);
	bool MakeWindow(std::wstring title, int width, int height);

	READ_ONLY_REF(std::wstring, Title);
	READ_ONLY(HWND, WindowHandle);
	READ_ONLY(HINSTANCE, InstanceHandle);

	static Application* m_Instance;
	
	READ_ONLY(float, Width);
	READ_ONLY(float, Height);

	int m_MouseState;
};

NS_EEL_END