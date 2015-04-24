#pragma once
#include "base/macro.h"
#include "utility/singleton.h"

NS_EEL_BEGIN

class Renderer : public Singleton<Renderer>
{
public:

private:
	Renderer();
	~Renderer();

	friend class Singleton<Renderer>;
};

NS_EEL_END