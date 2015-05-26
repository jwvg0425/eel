#include "stdafx.h"
#include "observerApp.h"
#include "config.h"
#include "networkMananger.h"

ObserverApp::ObserverApp()
{
}


ObserverApp::~ObserverApp()
{
}

LRESULT CALLBACK ObserverApp::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SOCKET selectedSocket = NULL;
	int errorId = NULL;
	switch(iMessage)
	{
		case WM_CREATE:
		return 0;

		case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

		case WM_SOCKET:
		selectedSocket = wParam;
		switch(WSAGETSELECTEVENT(lParam))
		{
			case FD_READ:
			GNetworkMananger->RecvPacket(selectedSocket);
			break;

			case FD_CLOSE:
			GNetworkMananger->OnClose(selectedSocket);
			break;

			case FD_WRITE:
			GNetworkMananger->OnWrite(selectedSocket);
			break;

			default:
			break;
		}
		return 0;

		default:
		return Application::WndProc(hWnd, iMessage, wParam, lParam);
	}
}
