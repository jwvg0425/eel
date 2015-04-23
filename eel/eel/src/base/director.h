#pragma once
#include <Windows.h>
#include "macro.h"
#include "utility/singleton.h"

NS_EEL_BEGIN

class Director : public Singleton<Director>
{
public:
	void GameLoop();

private:
	Director();
	~Director();

	READ_ONLY(HANDLE, WindowHandle);
	READ_ONLY(HINSTANCE, InstanceHandle);

	friend class Singleton<Director>;
};

NS_EEL_END