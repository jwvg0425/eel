#include "matrix3.h"

USING_NS_EEL;

eel::Matrix3::Matrix3() :
m_Value
(0, 0, 0,
0, 0, 0,
0, 0, 0)
{
}

eel::Matrix3::Matrix3
(FLOAT _00, FLOAT _01, FLOAT _02,
FLOAT _10, FLOAT _11, FLOAT _12,
FLOAT _20, FLOAT _21, FLOAT _22)
: m_Value
(_00, _01, _02,
_10, _11, _12,
_20, _21, _22)
{

}

eel::Matrix3::Matrix3(XMFLOAT3X3& value)
	:m_Value(value)
{

}

eel::Matrix3::Matrix3(XMMATRIX& value)
{
	XMStoreFloat3x3(&m_Value, value);
}


eel::Matrix3::~Matrix3()
{
}

eel::Matrix3::operator XMFLOAT3X3()
{
	return m_Value;
}

eel::Matrix3::operator XMMATRIX()
{
	return XMLoadFloat3x3(&m_Value);
}

FLOAT& eel::Matrix3::operator()(UINT row, UINT column)
{
	return m_Value(row, column);
}

FLOAT eel::Matrix3::operator()(UINT row, UINT column) const
{
	return m_Value(row, column);
}
