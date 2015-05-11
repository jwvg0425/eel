#include "matrix.h"

USING_NS_EEL;

XMMATRIX Matrix::RotationAxis(XMVECTOR axis, float angle)
{
	return XMMatrixRotationAxis(axis, angle);
}

XMMATRIX Matrix::RotationX(float angle)
{
	return XMMatrixRotationX(angle);
}

XMMATRIX Matrix::RotationY(float angle)
{
	return XMMatrixRotationY(angle);
}

XMMATRIX Matrix::RotationZ(float angle)
{
	return XMMatrixRotationZ(angle);
}
