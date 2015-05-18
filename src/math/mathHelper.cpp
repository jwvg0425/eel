#include "mathHelper.h"

USING_NS_EEL;

eel::Matrix4 eel::Math::inverseTranspose(Matrix4 mat)
{
	XMMATRIX A = mat;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	return XMMatrixTranspose(XMMatrixInverse(&det, A));
}
