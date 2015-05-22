#pragma once
#include "component/model.h"
#include "math/vector.h"
#include "math/ray.h"

NS_EEL_BEGIN

class DebugLine
{
public:
	DebugLine();
	~DebugLine();

	void SetLine(const Point3& pos1, const Point3& pos2, const Color4& color);
	void SetLine(const Vector3& pos1, const Vector3& pos2);
	void SetLine(const Ray& ray);

	CREATE_FUNC(DebugLine);

private:
	SPTR<Model> m_Model = nullptr;
};

NS_EEL_END