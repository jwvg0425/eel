#include "vector3.h"

USING_NS_EEL;

eel::Vector3::Vector3(float x, float y, float z)
	: m_Value(x, y, z)
{
}

eel::Vector3::Vector3(const XMFLOAT3& value)
	: m_Value(value)
{

}

eel::Vector3::Vector3(const XMVECTOR& value)
{
	XMStoreFloat3(&m_Value, value);
}

eel::Vector3::Vector3()
	: m_Value(0, 0, 0)
{

}

float eel::Vector3::Dot(CXMVECTOR rhs)
{
	Vector3 res = Vector3(XMVector3Dot(*this, rhs));

	return res.m_Value.x;
}

XMVECTOR eel::Vector3::Cross(CXMVECTOR rhs)
{
	return XMVector3Cross(*this, rhs);
}

float eel::Vector3::GetX() const
{
	return m_Value.x;
}

float eel::Vector3::GetY() const
{
	return m_Value.y;
}

float eel::Vector3::GetZ() const
{
	return m_Value.z;
}

void eel::Vector3::SetX(float x)
{
	m_Value.x = x;
}

void eel::Vector3::SetY(float y)
{
	m_Value.y = y;
}

void eel::Vector3::SetZ(float z)
{
	m_Value.z = z;
}

ARRAY<float, 3> eel::Vector3::GetArray() const
{
	ARRAY<float, 3> res = { m_Value.x, m_Value.y, m_Value.z };

	return res;
}

void eel::Vector3::SetArray(ARRAY<float, 3> arr)
{
	m_Value = arr.data();
}

Vector3::operator XMFLOAT3()
{
	return m_Value;
}

Vector3::operator XMVECTOR()
{
	return XMLoadFloat3(&m_Value);
}
