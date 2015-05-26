#pragma once
#include "eel.h"

class ObserverApp : public eel::Application
{
public:
	ObserverApp();
	~ObserverApp();

	LRESULT CALLBACK WndProc
		(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) override;

	void FinishLaunching() override;
};

