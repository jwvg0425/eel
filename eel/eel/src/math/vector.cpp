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
	Vector res = XMVector4Dot(*this, rhs);

	return res.m_Value.x;
}

Vector::operator XMFLOAT4()
{
	return m_Value;
}

Vector::operator XMVECTOR()
{
	return XMLoadFloat4(&m_Value);
}
