#pragma once
#include "eel.h"
#include "MovingCamera.h"

extern int GId;

class ObserverApp : public eel::Application
{
public:
	ObserverApp();
	~ObserverApp();

	LRESULT CALLBACK WndProc
		(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) override;

	void FinishLaunching() override;
};
