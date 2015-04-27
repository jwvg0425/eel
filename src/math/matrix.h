#pragma once
#include "base/macro.h"
#include <Windows.h>
#include <XNAMath.h>

NS_EEL_BEGIN

//XMMATRIX series's proxy class.
class Matrix
{
public:
	Matrix();
	~Matrix();

private:
	PROPERTY(XMFLOAT4X4, Value);
};

NS_EEL_END