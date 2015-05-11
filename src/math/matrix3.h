#pragma once
#include "base/macro.h"
#include <Windows.h>
#include <XNAMath.h>

NS_EEL_BEGIN

//XMMATRIX series's proxy class.
class Matrix3
{
public:
	Matrix3();
	~Matrix3();
	Matrix3(FLOAT _00, FLOAT _01, FLOAT _02,
		FLOAT _10, FLOAT _11, FLOAT _12,
		FLOAT _20, FLOAT _21, FLOAT _22);

	explicit Matrix3(const XMFLOAT3X3& value);
	explicit Matrix3(const XMMATRIX& value);

	Matrix3(const Matrix3& rhs) = default;

	operator XMFLOAT3X3();
	operator XMMATRIX();

	//get (row, column) data
	FLOAT& operator()(UINT row, UINT column);

	FLOAT operator()(UINT row, UINT column) const;

private:
	PROPERTY(XMFLOAT3X3, Value);
};

NS_EEL_END