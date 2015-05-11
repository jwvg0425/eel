#include "vector4.h"

USING_NS_EEL;

eel::Vector4::Vector4(float x, float y, float z, float w)
	: m_Value(x, y, z, w)
{
}

eel::Vector4::Vector4(const XMFLOAT4& value)
	: m_Value(value)
{

}

eel::Vector4::Vector4(const XMVECTOR& value)
{
	XMStoreFloat4(&m_Value, value);
}

eel::Vector4::Vector4()
	: m_Value(0, 0, 0, 0)
{

}

eel::Vector4::Vector4(float value)
	: m_Value(value, value, value, value)
{

}

float eel::Vector4::Dot(CXMVECTOR rhs)
{
	Vector4 res = Vector4(XMVector4Dot(*this, rhs));

	return res.m_Value.x;
}

XMVECTOR eel::Vector4::Cross(CXMVECTOR rhs)
{
	return XMVector3Cross(*this, rhs);
}

float eel::Vector4::GetX() const
{
	return m_Value.x;
}

float eel::Vector4::GetY() const
{
	return m_Value.y;
}

float eel::Vector4::GetZ() const
{
	return m_Value.z;
}

float eel::Vector4::GetW() const
{
	return m_Value.w;
}

void eel::Vector4::SetX(float x)
{
	m_Value.x = x;
}

void eel::Vector4::SetY(float y)
{
	m_Value.y = y;
}

void eel::Vector4::SetZ(float z)
{
	m_Value.z = z;
}

void eel::Vector4::SetW(float w)
{
	m_Value.w = w;
}

ARRAY<float, 4> eel::Vector4::GetArray() const
{
	ARRAY<float, 4> res = { m_Value.x, m_Value.y, m_Value.z, m_Value.w };

	return res;
}

void eel::Vector4::SetArray(ARRAY<float, 4> arr)
{
	m_Value = arr.data();
}

XMVECTOR eel::Vector4::Normalize()
{
	return XMVector4Normalize(*this);
}

XMVECTOR eel::Vector4::MultiplyAdd(XMVECTOR v1, XMVECTOR v2)
{
	return XMVectorMultiplyAdd(*this, v1, v2);
}

XMVECTOR eel::Vector4::Transform(XMMATRIX& matrix)
{
	return XMVector4Transform(*this, matrix);
}

Vector4::operator XMFLOAT4()
{
	return m_Value;
}

Vector4::operator XMVECTOR()
{
	return XMLoadFloat4(&m_Value);
}
