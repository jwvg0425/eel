#include "stdafx.h"
#include "Player.h"
#include "MyPacket.pb.h"
#include "config.h"
#include "networkManager.h"

Player::Player()
{
}


Player::~Player()
{
}


void Player::RequestLogin()
{
	static int id = 300;
	mPlayerId = id++;
	MyPacket::LoginRequest loginRequest;
	loginRequest.set_playerid(mPlayerId);

	GNetworkManager->SendPacket(MyPacket::PKT_CS_LOGIN, loginRequest);
}

void Player::ResponseLogin(bool success, int pid, float x, float y, float z, const char* name)
{
	if(success)
	{
		mPlayerId = pid;
		mPosX = x;
		mPosY = y;
		mPosZ = z;
		mPlayerName = name;

		std::stringstream reslog;
		reslog << "LOG: Player Login : PID[" << mPlayerId << "], X[" << mPosX << "], Y[" << mPosY << "], Z[" << mPosZ << "], NAME[" << mPlayerName << "]" << std::endl;
		std::string logString = reslog.str();
		std::cout << logString;
	}
}


void Player::PlayerReset()
{
	mPlayerName.clear();
	mComment.clear();
	mPlayerId = -1;
	mIsValid = false;
	mPosX = mPosY = mPosZ = 0;
}

void Player::RequestMove(float x, float y, float z)
{
	MyPacket::MoveRequest moveRequest;
	
	moveRequest.set_playerid(mPlayerId);
	MyPacket::Position* newPos = new MyPacket::Position();
	newPos->set_x(x);
	newPos->set_y(y);
	newPos->set_z(z);
	moveRequest.set_allocated_playerpos(newPos);

	GNetworkManager->SendPacket(MyPacket::PKT_CS_MOVE, moveRequest);
}

void Player::ResponseMove(bool success, float x, float y, float z)
{
	std::stringstream logStream;
	if(success)
	{
		mPosX = x;
		mPosY = y;
		mPosZ = z;
		logStream << "Player [" << mPlayerId << "]"
			<< " move to (" << mPosX << ", " << mPosY << ", " << mPosZ << ")" << std::endl;
		
	}
	else
	{
		logStream << "Player [" << mPlayerId << "]"
			<< " fail to move."<< std::endl;
	}
	std::string logString = logStream.str();
	std::cout << logString;
}

void Player::RequestChat(const std::string& message)
{
	MyPacket::ChatRequest chatRequest;
	chatRequest.set_playermessage(message);
	chatRequest.set_playerid(mPlayerId);
	GNetworkManager->SendPacket(MyPacket::PKT_CS_CHAT, chatRequest);
}

void Player::ResponseChat(bool success, const std::string& name, const std::string& message)
{
	std::stringstream logStream;
	std::string logString;
	if(success)
	{
		logStream << "[" << name << "]: " << message << std::endl;
	}
	else
	{
		logStream << "[" << name << "]: " << "message Failed" << std::endl;
	}

	logString = logStream.str();
	std::cout << logString;
}