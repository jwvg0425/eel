#pragma once
#include "base/macro.h"
#include <Windows.h>
#include <XNAMath.h>

NS_EEL_BEGIN

//XMMATRIX series's proxy class.
class Matrix
{
private:
	XMFLOAT4X4 m_Value;
};

NS_EEL_END