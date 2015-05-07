#include "vector.h"

USING_NS_EEL;

eel::Vector::Vector(float x, float y, float z, float w)
: m_Value(x, y, z, w)
{
}

eel::Vector::Vector(XMFLOAT4 value)
: m_Value(value)
{

}

eel::Vector::Vector(XMVECTOR value)
{
	XMStoreFloat4(&m_Value, value);
}

eel::Vector::Vector()
: m_Value(0, 0, 0, 0)
{

}

float eel::Vector::Dot(CXMVECTOR rhs)
{
	Vector res = Vector(XMVector4Dot(*this, rhs));

	return res.m_Value.x;
}

XMVECTOR eel::Vector::Cross(CXMVECTOR rhs)
{
	return XMVector3Cross(*this, rhs);
}

float eel::Vector::GetX()
{
	return m_Value.x;
}

float eel::Vector::GetY()
{
	return m_Value.y;
}

float eel::Vector::GetZ()
{
	return m_Value.z;
}

float eel::Vector::GetW()
{
	return m_Value.w;
}

void eel::Vector::SetX(float x)
{
	m_Value.x = x;
}

void eel::Vector::SetY(float y)
{
	m_Value.y = y;
}

void eel::Vector::SetZ(float z)
{
	m_Value.z = z;
}

void eel::Vector::SetW(float w)
{
	m_Value.w = w;
}

ARRAY<float, 4> eel::Vector::GetArray()
{
	ARRAY<float, 4> res = { m_Value.x, m_Value.y, m_Value.z, m_Value.w };

	return res;
}

void eel::Vector::SetArray(ARRAY<float, 4> arr)
{
	m_Value = arr.data();
}

Vector::operator XMFLOAT4()
{
	return m_Value;
}

Vector::operator XMVECTOR()
{
	return XMLoadFloat4(&m_Value);
}
