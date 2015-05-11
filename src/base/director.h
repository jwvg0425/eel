#pragma once
#include "base/macro.h"
#include "utility/singleton.h"
#include "component/scene.h"

NS_EEL_BEGIN

class Director : public Object, public Singleton<Director>
{
public:
	Director();
	~Director();

	void GameLoop();

	void RunWithScene(SPTR<Scene> scene);

private:
	SPTR<Scene> m_RunningScene = nullptr;
};

NS_EEL_END