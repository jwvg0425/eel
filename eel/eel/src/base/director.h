#pragma once
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

	friend class Singleton<Director>;
};

NS_EEL_END