#pragma once
#include "base/macro.h"
#include "math/vector.h"

NS_EEL_BEGIN

template<typename RawVertex>
class VertexWrapper
{
public:
	VertexWrapper();
	VertexWrapper(const VertexWrapper& rhs) = default;
	VertexWrapper(const RawVertex& data) : m_VertexData(data)
	{
	}

	//RawVertex must have Point3 member named "m_Pos"
	const Point3* GetPos() const
	{
		__if_exists( RawVertex::m_Pos )
		{
			return &m_VertexData.m_Pos;
		}
		return  nullptr;
	}

	RawVertex	GetData() const
	{
		return m_VertexData;
	}

private:
	RawVertex m_VertexData;
};

NS_EEL_END
