﻿#include "mathHelper.h"

USING_NS_EEL;

eel::Matrix4 eel::Math::inverseTranspose(Matrix4 mat)
{
	XMMATRIX A = mat;
	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

	XMVECTOR det = XMMatrixDeterminant(A);
	return XMMatrixTranspose(XMMatrixInverse(&det, A));
}

BOOL eel::Math::IntersectRayTriangle(FXMVECTOR Origin, FXMVECTOR Direction, FXMVECTOR V0, CXMVECTOR V1, CXMVECTOR V2, FLOAT* pDist)
{
	{
		XMASSERT(pDist);

		static const XMVECTOR Epsilon =
		{
			1e-20f, 1e-20f, 1e-20f, 1e-20f
		};

		XMVECTOR Zero = XMVectorZero();

		XMVECTOR e1 = V1 - V0;
		XMVECTOR e2 = V2 - V0;

		// p = Direction ^ e2;
		XMVECTOR p = XMVector3Cross(Direction, e2);

		// det = e1 * p;
		XMVECTOR det = XMVector3Dot(e1, p);

		XMVECTOR u, v, t;

		if (XMVector3GreaterOrEqual(det, Epsilon))
		{
			// Determinate is positive (front side of the triangle).
			XMVECTOR s = Origin - V0;

			// u = s * p;
			u = XMVector3Dot(s, p);

			XMVECTOR NoIntersection = XMVectorLess(u, Zero);
			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(u, det));

			// q = s ^ e1;
			XMVECTOR q = XMVector3Cross(s, e1);

			// v = Direction * q;
			v = XMVector3Dot(Direction, q);

			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(v, Zero));
			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(u + v, det));

			// t = e2 * q;
			t = XMVector3Dot(e2, q);

			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(t, Zero));

			if (XMVector4EqualInt(NoIntersection, XMVectorTrueInt()))
				return FALSE;
		}
		else if (XMVector3LessOrEqual(det, -Epsilon))
		{
			// Determinate is negative (back side of the triangle).
			XMVECTOR s = Origin - V0;

			// u = s * p;
			u = XMVector3Dot(s, p);

			XMVECTOR NoIntersection = XMVectorGreater(u, Zero);
			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(u, det));

			// q = s ^ e1;
			XMVECTOR q = XMVector3Cross(s, e1);

			// v = Direction * q;
			v = XMVector3Dot(Direction, q);

			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(v, Zero));
			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorLess(u + v, det));

			// t = e2 * q;
			t = XMVector3Dot(e2, q);

			NoIntersection = XMVectorOrInt(NoIntersection, XMVectorGreater(t, Zero));

			if (XMVector4EqualInt(NoIntersection, XMVectorTrueInt()))
				return FALSE;
		}
		else
		{
			// Parallel ray.
			return FALSE;
		}

		XMVECTOR inv_det = XMVectorReciprocal(det);

		t *= inv_det;

		// u * inv_det and v * inv_det are the barycentric cooridinates of the intersection.

		// Store the x-component to *pDist
		XMStoreFloat(pDist, t);

		return TRUE;
	}
}
