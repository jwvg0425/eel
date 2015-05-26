#pragma once
#include "CircularBuffer.h"
extern NetworkMananger* GNetworkMananger;
extern char CONNECT_ADDR[32];
extern unsigned short CONNECT_PORT;

enum ClosedReasonType
{
	CRT_NORMAL,
	CRT_INIT,
	CRT_RECV,
	CRT_SEND,
	CRT_SELECT,
	CRT_MAX,
};

class NetworkMananger
{
public:
	NetworkMananger();
	~NetworkMananger();

	bool InitSocket();
	
	void OnRead(SOCKET socket);
	void OnClose(SOCKET socket);
	void OnWrite(SOCKET socket);

	bool SendPacket(short packetType, const protobuf::MessageLite& payload);
	void RecvPacket();
	bool PostSend(const char* data, size_t len);
	void CloseSocketWithReason(ClosedReasonType reason);

private:
	SOCKET mSocket;
	CircularBuffer mRecvBuffer;
	CircularBuffer mSendBuffer;
};

