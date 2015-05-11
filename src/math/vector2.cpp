#include "vector2.h"

USING_NS_EEL;

eel::Vector2::Vector2(float x, float y)
	: m_Value(x, y)
{
}

eel::Vector2::Vector2(const XMFLOAT2& value)
	: m_Value(value)
{

}

eel::Vector2::Vector2(const XMVECTOR& value)
{
	XMStoreFloat2(&m_Value, value);
}

eel::Vector2::Vector2()
	: m_Value(0, 0)
{

}

float eel::Vector2::Dot(CXMVECTOR rhs)
{
	Vector2 res = Vector2(XMVector2Dot(*this, rhs));

	return res.m_Value.x;
}

XMVECTOR eel::Vector2::Cross(CXMVECTOR rhs)
{
	return XMVector2Cross(*this, rhs);
}

float eel::Vector2::GetX() const
{
	return m_Value.x;
}

float eel::Vector2::GetY() const
{
	return m_Value.y;
}

void eel::Vector2::SetX(float x)
{
	m_Value.x = x;
}

void eel::Vector2::SetY(float y)
{
	m_Value.y = y;
}

ARRAY<float, 2> eel::Vector2::GetArray() const
{
	ARRAY<float, 2> res = { m_Value.x, m_Value.y };

	return res;
}

void eel::Vector2::SetArray(ARRAY<float, 2> arr)
{
	m_Value = arr.data();
}

Vector2::operator XMFLOAT2()
{
	return m_Value;
}

Vector2::operator XMVECTOR()
{
	return XMLoadFloat2(&m_Value);
}
