#pragma once
#include "base/macro.h"
#include <Windows.h>
#include <XNAMath.h>

NS_EEL_BEGIN

//XMMATRIX series's proxy class.
class Matrix4
{
public:
	Matrix4();
	~Matrix4();
	Matrix4(FLOAT _00, FLOAT _01, FLOAT _02, FLOAT _03,
			FLOAT _10, FLOAT _11, FLOAT _12, FLOAT _13,
			FLOAT _20, FLOAT _21, FLOAT _22, FLOAT _23,
			FLOAT _30, FLOAT _31, FLOAT _32, FLOAT _33);

	explicit Matrix4(const XMFLOAT4X4& value);
	explicit Matrix4(const XMMATRIX& value);

	Matrix4(const Matrix4& rhs) = default;

	operator XMFLOAT4X4();
	operator XMMATRIX();

	//get (row, column) data
	FLOAT& operator()(UINT row, UINT column);

	FLOAT operator()(UINT row, UINT column) const;

private:
	PROPERTY(XMFLOAT4X4, Value);
};

NS_EEL_END