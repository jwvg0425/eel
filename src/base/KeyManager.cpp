#include "KeyManager.h"
#include "Director.h"

USING_NS_EEL;

eel::KeyManager::KeyManager()
{
	for (int i = 0; i < Key::NUM; i++)
	{
		m_States[i] = Key::FREE;
		m_OldStates[i] = Key::FREE;
	}

	Director::GetInstance()->RegisterEvent(EventType::UPDATE, this, &eel::KeyManager::Update);
}

void eel::KeyManager::Update(const UpdateEvent& e)
{
	for (int i = 0; i < Key::NUM; i++)
	{
		int nowState = GetAsyncKeyState(i);

		if (nowState & 0x8000)
		{
			switch (m_OldStates[i])
			{
			case Key::FREE:
			case Key::PULL:
				m_States[i] = Key::PUSH;
				break;
			case Key::PUSH:
			case Key::HOLD:
				m_States[i] = Key::HOLD;
				break;
			}
		}
		else
		{
			switch (m_OldStates[i])
			{
			case Key::PULL:
			case Key::FREE:
				m_States[i] = Key::FREE;
				break;
			case Key::PUSH:
			case Key::HOLD:
				m_States[i] = Key::PULL;
				break;
			}
		}

		m_OldStates[i] = m_States[i];
	}
}

Key::State eel::KeyManager::GetKeyState(int keyCode)
{
	_ASSERT(keyCode >= 0 && keyCode < Key::NUM);

	return m_States[keyCode];
}

bool eel::KeyManager::IsKeyState(int keyCode, Key::State state)
{
	_ASSERT(keyCode >= 0 && keyCode < Key::NUM);

	return (m_States[keyCode] & state) != 0;
}
