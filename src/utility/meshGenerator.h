#pragma once
#include "base/macro.h"
#include "render/vertex/posColor.h"
#include "render/vertex/posNormal.h"
#include "render/vertex/posBasic.h"
#include <vector>

NS_EEL_BEGIN

namespace MeshGenerator
{
	void CreateColorCube(float width, float height, float depth, Color4 color, OUT std::vector<PosColor>& vertices, OUT std::vector<UINT>& indices);
	void CreateNormalCube(float width, float height, float depth, OUT std::vector<PosNormal>& vertices, OUT std::vector<UINT>& indices);
	void CreateCube(float width, float height, float depth, OUT std::vector<PosBasic>& vertices, OUT std::vector<UINT>& indices);

	void CreateNormalSphere(float radius, UINT sliceCount, UINT stackCount, OUT std::vector<PosNormal>& vertices, OUT std::vector<UINT>& indices);
};

NS_EEL_END