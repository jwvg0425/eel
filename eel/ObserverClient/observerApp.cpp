#include "stdafx.h"
#include "observerApp.h"
#include "config.h"
#include "networkManager.h"
#include "utility/log.h"
#include "gameScene.h"
#include "MovingCamera.h"

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
				if (WSAAsyncSelect(selectedSocket, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE))
				{
					eel::LOG(L"NetworkManager::InitSocket() WSAAsyncSelect error: %d\n", GetLastError());
					return false;
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

	eel::Renderer::GetInstance()->
		SetScreenBackgroundColor(eel::Color4(0.6f, 0.8f, 0.3f, 1.0f));

	eel::Renderer::GetInstance()->
		SetScreenCamera(MovingCamera::Create(eel::Point3(0.0f, 20.0f, 30.0f), eel::Point3(0.0f, 0.0f, 0.0f), eel::Vector3(0.0f, 1.0f, 0.0f)));

	eel::Director::GetInstance()->
		RunWithScene(GameScene::Create());
}
