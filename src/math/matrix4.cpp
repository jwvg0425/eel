#include "matrix4.h"

USING_NS_EEL;

eel::Matrix4::Matrix4() :
m_Value
(0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0)
{
}

eel::Matrix4::Matrix4
(FLOAT _00, FLOAT _01, FLOAT _02, FLOAT _03,
 FLOAT _10, FLOAT _11, FLOAT _12, FLOAT _13,
 FLOAT _20, FLOAT _21, FLOAT _22, FLOAT _23,
 FLOAT _30, FLOAT _31, FLOAT _32, FLOAT _33)
 : m_Value
 (_00, _01, _02, _03,
  _10, _11, _12, _13,
  _20, _21, _22, _23,
  _30, _31, _32, _33)
{

}

eel::Matrix4::Matrix4(XMFLOAT4X4& value)
:m_Value(value)
{

}

eel::Matrix4::Matrix4(XMMATRIX& value)
{
	XMStoreFloat4x4(&m_Value, value);
}


eel::Matrix4::~Matrix4()
{
}

eel::Matrix4::operator XMFLOAT4X4()
{
	return m_Value;
}

eel::Matrix4::operator XMMATRIX()
{
	return XMLoadFloat4x4(&m_Value);
}

FLOAT& eel::Matrix4::operator()(UINT row, UINT column)
{
	return m_Value(row, column);
}

FLOAT eel::Matrix4::operator()(UINT row, UINT column) const
{
	return m_Value(row, column);
}
