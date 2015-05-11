#pragma once
#include "base/macro.h"
#include "utility/singleton.h"

NS_EEL_BEGIN

class EffectImpl
{
public:

private:
};

template <typename T>
class Effect : public EffectImpl, public Singleton<T>
{
};

NS_EEL_END