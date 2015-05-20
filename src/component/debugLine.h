#pragma once
#include "component/model.h"
#include "math/ray.h"
#include "math/vector.h"

NS_EEL_BEGIN

class DebugLine
{
public:
	DebugLine();
	DebugLine(const Ray& ray);
	DebugLine(const Point3& pos1, const Point3& pos2);
	DebugLine(const Point3& pos1, const Point3& pos2, const Color4& color);

	~DebugLine();

private:
	SPTR<Model> m_Model;
};

NS_EEL_END