#pragma once
#include "base/macro.h"
#include "utility/Clonable.h"
#include <Windows.h>
#include <xnamath.h>

NS_EEL_BEGIN

//XMVECTOR series's proxy class.
class Vector
{
public:

private:
	XMFLOAT4 m_Value;
};

NS_EEL_END