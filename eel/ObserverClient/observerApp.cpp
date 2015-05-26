#include "stdafx.h"
#include "observerApp.h"
#include "config.h"
#include "networkManager.h"
#include "utility/log.h"

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
	int opt = 1;

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
			GNetworkManager->RecvPacket();
			break;

			case FD_CLOSE:
			GNetworkManager->OnClose(selectedSocket);
			break;

			case FD_WRITE:
			GNetworkManager->OnWrite(selectedSocket);
			break;
			case FD_CONNECT:
				if (0 != setsockopt(selectedSocket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int)))
				{
					eel::LOG(L"NetworkManager::InitSocket() TCP_NODELAY error: %d\n", GetLastError());
					break;
				}
				break;

			default:
			break;
		}
		return 0;

		default:
		return Application::WndProc(hWnd, iMessage, wParam, lParam);
	}
}

void ObserverApp::FinishLaunching()
{
	GNetworkManager = new NetworkManager;
}
