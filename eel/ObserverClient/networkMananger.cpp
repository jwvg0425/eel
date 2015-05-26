#include "stdafx.h"
#include "networkMananger.h"
#include "utility/log.h"
#include "ObserverApp.h"
#include "config.h"
#include "PacketInterface.h"

static NetworkMananger* GNetworkMananger = nullptr;
char CONNECT_ADDR[32] = {0, };
unsigned short CONNECT_PORT = 0;

NetworkMananger::NetworkMananger()
	:mRecvBuffer(BUF_SIZE), mSendBuffer(BUF_SIZE)
{
	if(!InitSocket())
	{
		CloseSocketWithReason(CRT_INIT);
	}
}


NetworkMananger::~NetworkMananger()
{
}

bool NetworkMananger::InitSocket()
{
	WSADATA wsaData;
	if(0 != WSAStartup(( 2, 2 ), &wsaData))
	{
		eel::LOG(L"NetworkManager::InitSocket() WSAStartup error: %d\n", GetLastError());
		return false;
	}

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(mSocket == INVALID_SOCKET)
	{
		eel::LOG(L"NetworkManager::InitSocket() socket create error: %d\n", GetLastError());
		return false;
	}

	HWND hWnd = ObserverApp::GetInstance()->GetWindowHandle();

	if(WSAAsyncSelect(mSocket, hWnd, WM_SOCKET, ( FD_CLOSE | FD_READ | FD_WRITE)))
	{
		eel::LOG(L"NetworkManager::InitSocket() WSAAsyncSelect error: %d\n", GetLastError());
		return false;
	}


	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(CONNECT_ADDR);
	addr.sin_port = htons(CONNECT_PORT);

	if(0 != connect(mSocket, (LPSOCKADDR) ( &addr ), sizeof(addr)))
	{
		eel::LOG(L"NetworkManager::InitSocket() connect error: %d\n", GetLastError());
		return false;
	}

	int opt = 1;
	if(SOCKET_ERROR == setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (const char*) &opt, sizeof(int)))
	{
		eel::LOG(L"NetworkManager::InitSocket() TCP_NODELAY error: %d\n", GetLastError());
		return false;
	}

	return true;
}

void NetworkMananger::OnClose(SOCKET socket)
{
	if(socket != mSocket)
		return;

	CloseSocketWithReason(CRT_NORMAL);
}

void NetworkMananger::CloseSocketWithReason(ClosedReasonType reason)
{
	eel::LOG(L"Connect Closed with %d\n", reason);
	closesocket(mSocket);

	//접속 종료되면 클라이언트 종료
	HWND hWnd = ObserverApp::GetInstance()->GetWindowHandle();
	SendMessage(hWnd, WM_DESTROY, NULL, NULL);
}

void NetworkMananger::OnWrite(SOCKET socket)
{
	if(socket != mSocket)
		return;

	if(mSendBuffer.GetContiguiousBytes() == 0)
		return;

	DWORD sendbytes = send(mSocket, mSendBuffer.GetBufferStart(), mSendBuffer.GetContiguiousBytes(), 0);
	if(sendbytes == SOCKET_ERROR)
	{
		eel::LOG(L"NetworkManager::OnWrite() send error: %d\n", GetLastError());
		CloseSocketWithReason(CRT_RECV);
		return;
	}
}

bool NetworkMananger::PostSend(const char* data, size_t len)
{
	if(mSendBuffer.GetFreeSpaceSize() < len)
		return false;

	char* destData = mSendBuffer.GetBuffer();
	memcpy(destData, data, len);
	mSendBuffer.Commit(len);

	return true;
}

void NetworkMananger::OnRead(SOCKET socket)
{
	if(socket != mSocket)
		return;

	DWORD recvByte = recv(mSocket, mRecvBuffer.GetBuffer(), mRecvBuffer.GetFreeSpaceSize(), 0);

	if(recvByte == SOCKET_ERROR)
	{
		int errorId = WSAGetLastError();
		if(errorId != WSAEWOULDBLOCK)
		{
			eel::LOG(L"NetworkManager::OnRead() recv error: %d\n", GetLastError());
			CloseSocketWithReason(CRT_RECV);
			return;
		}
	}

	mRecvBuffer.Commit(recvByte);
	RecvPacket();
}

bool NetworkMananger::SendPacket(short packetType, const protobuf::MessageLite& payload)
{
	int totalSize = payload.ByteSize() + HEADER_SIZE;
	if(mSendBuffer.GetFreeSpaceSize() < totalSize)
		return false;

	protobuf::io::ArrayOutputStream arrayOutputStream(mSendBuffer.GetBuffer(), totalSize);
	protobuf::io::CodedOutputStream codedOutputStream(&arrayOutputStream);

	PacketHeader header;
	header.mSize = payload.ByteSize();
	header.mType = packetType;

	codedOutputStream.WriteRaw(&header, HEADER_SIZE);
	payload.SerializeToCodedStream(&codedOutputStream);

	mSendBuffer.Commit(totalSize);

	return true;
}
