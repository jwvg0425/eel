﻿#pragma once
#include "base/object.h"
#include "utility/singleton.h"
#include "base/event/updateEvent.h"

//존재하지 않는 키코드 정의
#define		VK_0	0x30
#define		VK_1	0x31
#define		VK_2	0x32
#define		VK_3	0x33
#define		VK_4	0x34
#define		VK_5	0x35
#define		VK_6	0x36
#define		VK_7	0x37
#define		VK_8	0x38
#define		VK_9	0x39

#define 	VK_A 	0x41 
#define 	VK_B 	0x42 
#define 	VK_C 	0x43 
#define 	VK_D 	0x44 
#define 	VK_E 	0x45 
#define 	VK_F 	0x46 
#define 	VK_G 	0x47 
#define 	VK_H 	0x48 
#define 	VK_I 	0x49 
#define 	VK_J 	0x4A 
#define 	VK_K 	0x4B 
#define 	VK_L 	0x4C 
#define 	VK_M 	0x4D 
#define 	VK_N 	0x4E 
#define 	VK_O 	0x4F 
#define 	VK_P 	0x50 
#define 	VK_Q 	0x51 
#define 	VK_R 	0x52 
#define 	VK_S 	0x53 
#define 	VK_T 	0x54 
#define 	VK_U 	0x55 
#define 	VK_V 	0x56 
#define 	VK_W 	0x57
#define 	VK_X 	0x58
#define 	VK_Y 	0x59
#define 	VK_Z 	0x5A

NS_EEL_BEGIN

namespace Key
{
	enum State
	{
		FREE = 0x0, //안 눌림
		PULL = 0x1, //눌렀다 뗀 순간
		PUSH = 0x2, //딱 누른 순간 
		HOLD = 0x4,  //누르고 있는 중
		PRESS = PUSH | HOLD, //누른 순간이든 누르고 있었든 어쨌든 키가 눌림
		NONE = FREE | PULL // 딱 뗀 순간이든 계속 안 누르고 있었든 키가 안 눌림
	};

	static const int NUM = 256;
};

class KeyManager : public Object, public Singleton < KeyManager >
{
public:
	KeyManager();
	virtual ~KeyManager() = default;

	void Update(const UpdateEvent& e);
	Key::State GetKeyState(int keyCode);
	bool IsKeyState(int keyCode, Key::State state);

private:
	Key::State m_States[Key::NUM];
	Key::State m_OldStates[Key::NUM];
};

NS_EEL_END