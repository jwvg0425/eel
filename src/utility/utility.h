#pragma once
#include "base/macro.h"
#include "component/model.h"
#include "math/ray.h"
#include "math/mathHelper.h"

NS_EEL_BEGIN

template<typename T>
struct is_offset_exist
{
	template<typename Arg>
	static auto Fn(int)
		->decltype(Arg::offset, std::true_type());
	template<typename Arg>
	static auto Fn(...)
		->std::false_type;
	using type = decltype(Fn<T>(0));
	static const bool value = type::value;
};

int Pick(const Model& model, const Ray& ray)
{
	XMMATRIX W = XMLoadFloat4x4(&model.GetWorld().GetValue());
	XMMATRIX invWorld = XMMatrixInverse(&XMMatrixDeterminant(W), W);

	Ray testRay;

	testRay.SetRayOrigin(XMVector3TransformCoord(ray.GetRayOrigin(), invWorld));
	testRay.SetRayDirection(XMVector3TransformCoord(ray.GetRayDirection(), invWorld));
	testRay.SetRayDirection(testRay.GetRayDirection().Normalize());

	float tmin = 0.0f;
	int pickedTriangle = -1;
	
	for(UINT i = 0; i < model.GetIndexCount() / 3; ++i)
	{
		tmin = Math::INF;
		// Indices for this triangle.
		UINT i0 = model.GetIndex(i * 3 + 0);
		UINT i1 = model.GetIndex(i * 3 + 1);
		UINT i2 = model.GetIndex(i * 3 + 2);

		// Vertices for this triangle.
		Point3  v0 = *( model.GetPosByIndex(i0) );
		Point3	v1 = *( model.GetPosByIndex(i1) );
		Point3  v2 = *( model.GetPosByIndex(i2) );

		// We have to iterate over all the triangles in order to find the nearest intersection.
		float t = 0.0f;
		if(Math::IntersectRayTriangle(
			ray.GetRayOrigin(),
			ray.GetRayDirection(),
			v0, v1, v2, &t))
		{
			if(t < tmin)
			{
				// This is the new nearest picked triangle.
				tmin = t;
				pickedTriangle = i;
			}
		}
	}

	return pickedTriangle;
}

NS_EEL_END