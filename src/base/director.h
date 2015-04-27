#pragma once
#include "base/macro.h"
#include "utility/singleton.h"
#include "base/object.h"

NS_EEL_BEGIN

class Director : public Object, public Singleton<Director>
{
public:
	Director();
	~Director();

	void GameLoop();

private:
};

NS_EEL_END