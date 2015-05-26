#pragma once
#include "CircularBuffer.h"
#include "MyPacket.pb.h"

class NetworkManager;
extern NetworkManager* GNetworkManager;
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

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	bool InitSocket();
	
	void OnRead(SOCKET socket);
	void OnClose(SOCKET socket);
	void OnWrite(SOCKET socket);

	bool SendPacket(short packetType, const google::protobuf::MessageLite& payload);
	void RecvPacket();
	bool PostSend(const char* data, size_t len);
	void CloseSocketWithReason(ClosedReasonType reason);

private:
	SOCKET mSocket;
	CircularBuffer mRecvBuffer;
	CircularBuffer mSendBuffer;
};

