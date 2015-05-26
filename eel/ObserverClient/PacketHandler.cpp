#include "stdafx.h"
#include "PacketInterface.h"
#include "networkManager.h"
#include "utility/log.h"
#include "observerApp.h"

//@{ Handler Helper

typedef void(*HandlerFunc)(PacketHeader& pktBase, protobuf::io::CodedInputStream& payloadStream);

static HandlerFunc HandlerTable[MAX_PKT_TYPE];

static void DefaultHandler(PacketHeader& pktBase, protobuf::io::CodedInputStream& payloadStream)
{
	
	printf_s("Default Handler...PKT ID: %d\n", pktBase.mType);
}

struct InitializeHandlers
{
	InitializeHandlers()
	{
		for (int i = 0; i < MAX_PKT_TYPE; ++i)
			HandlerTable[i] = DefaultHandler;
	}
} _init_handlers_;

struct RegisterHandler
{
	RegisterHandler(int pktType, HandlerFunc handler)
	{
		HandlerTable[pktType] = handler;
	}
};

#define REGISTER_HANDLER(PKT_TYPE)	\
	static void Handler_##PKT_TYPE(PacketHeader& pktBase, protobuf::io::CodedInputStream& payloadStream); \
	static RegisterHandler _register_##PKT_TYPE(PKT_TYPE, Handler_##PKT_TYPE); \
	static void Handler_##PKT_TYPE(PacketHeader& pktBase, protobuf::io::CodedInputStream& payloadStream)



/// 패킷 파싱하고 처리

void NetworkManager::RecvPacket()
{
	if(mRecvBuffer.GetContiguiousBytes() == 0)
		return;

	protobuf::io::ArrayInputStream arrayInputStream(mRecvBuffer.GetBufferStart(), mRecvBuffer.GetContiguiousBytes());
	protobuf::io::CodedInputStream codedInputStream(&arrayInputStream);

	PacketHeader packetheader;

	while(codedInputStream.ReadRaw(&packetheader, HEADER_SIZE))
	{
		const void* payloadPos = nullptr;
		int payloadSize = 0;

		codedInputStream.GetDirectBufferPointer(&payloadPos, &payloadSize);

		if(payloadSize < packetheader.mSize) ///< 패킷 본체 사이즈 체크
			break;

		if(packetheader.mType >= MAX_PKT_TYPE || packetheader.mType <= 0)
		{
			//연결 처리
			break;
		}

		/// payload 읽기
		protobuf::io::ArrayInputStream payloadArrayStream(payloadPos, packetheader.mSize);
		protobuf::io::CodedInputStream payloadInputStream(&payloadArrayStream);

		/// packet dispatch...
		HandlerTable[packetheader.mType](packetheader, payloadInputStream);

		/// 읽은 만큼 전진 및 버퍼에서 제거
		codedInputStream.Skip(packetheader.mSize); ///< readraw에서 헤더 크기만큼 미리 전진했기때문
		mRecvBuffer.Remove(HEADER_SIZE + packetheader.mSize);

	}
}


/////////////////////////////////////////////////////////////

using namespace MyPacket;

REGISTER_HANDLER(PKT_SC_LOGIN)
{
	LoginResult loginResult;
	if (false == loginResult.ParseFromCodedStream(&payloadStream))
	{
		//Disconnect
		return;
	}

	bool success = loginResult.playerid() != -1;

	const Position& pos = loginResult.playerpos();

	GId = loginResult.playerid();

	eel::Renderer::GetInstance()->GetCurrentCamera()->SetEyePos(eel::Point3(pos.x(), pos.y(), pos.z()));

	//mPlayer->ResponseLogin(success, loginResult.playerid(),pos.x(), pos.y(), pos.z(), loginResult.playername().c_str());
}

REGISTER_HANDLER(PKT_SC_MOVE)
{
	MoveResult moveResult;
	if(false == moveResult.ParseFromCodedStream(&payloadStream))
	{
		//Disconnect
		return;
	}

	bool success = moveResult.playerid() != -1;

	const Position& pos = moveResult.playerpos();

	if (moveResult.playerid() == GId)
		return;

	auto player = eel::Director::GetInstance()->GetRunningScene()->GetChildByName(std::to_string(moveResult.playerid()));

	if (player == nullptr)
	{
	}

	//mPlayer->ResponseMove(success, pos.x(), pos.y(), pos.z());
}

REGISTER_HANDLER(PKT_SC_CHAT)
{
	ChatResult chatResult;
	if(false == chatResult.ParseFromCodedStream(&payloadStream))
	{
		//Disconnect
		return;
	}

	bool success = true; //mPlayer->GetPlayerName() == chatResult.playername();
	//mPlayer->ResponseChat(success, chatResult.playername(), chatResult.playermessage());
}

REGISTER_HANDLER(PKT_SC_LOGOUT)
{
	LogoutResult logoutResult;
	if (false == logoutResult.ParseFromCodedStream(&payloadStream))
	{
		return;
	}
}