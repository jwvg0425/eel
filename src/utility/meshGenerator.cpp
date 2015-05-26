﻿#include "meshGenerator.h"

void eel::MeshGenerator::CreateColorCube(float width, float height, float depth, Color4 color, OUT std::vector<PosColor>& vertices, OUT std::vector<UINT>& indices)
{
	PosColor v[24];

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	// Fill in the front face vertex data.
	v[0] = PosColor(-w2, -h2, -d2, color);
	v[1] = PosColor(-w2, +h2, -d2, color);
	v[2] = PosColor(+w2, +h2, -d2, color);
	v[3] = PosColor(+w2, -h2, -d2, color);

	// Fill in the back face vertex data.
	v[4] = PosColor(-w2, -h2, +d2, color);
	v[5] = PosColor(+w2, -h2, +d2, color);
	v[6] = PosColor(+w2, +h2, +d2, color);
	v[7] = PosColor(-w2, +h2, +d2, color);

	// Fill in the top face vertex data.
	v[8] = PosColor(-w2, +h2, -d2, color);
	v[9] = PosColor(-w2, +h2, +d2, color);
	v[10] = PosColor(+w2, +h2, +d2, color);
	v[11] = PosColor(+w2, +h2, -d2, color);

	// Fill in the bottom face vertex data.
	v[12] = PosColor(-w2, -h2, -d2, color);
	v[13] = PosColor(+w2, -h2, -d2, color);
	v[14] = PosColor(+w2, -h2, +d2, color);
	v[15] = PosColor(-w2, -h2, +d2, color);

	// Fill in the left face vertex data.
	v[16] = PosColor(-w2, -h2, +d2, color);
	v[17] = PosColor(-w2, +h2, +d2, color);
	v[18] = PosColor(-w2, +h2, -d2, color);
	v[19] = PosColor(-w2, -h2, -d2, color);

	// Fill in the right face vertex data.
	v[20] = PosColor(+w2, -h2, -d2, color);
	v[21] = PosColor(+w2, +h2, -d2, color);
	v[22] = PosColor(+w2, +h2, +d2, color);
	v[23] = PosColor(+w2, -h2, +d2, color);

	vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	indices.assign(&i[0], &i[36]);
}

void eel::MeshGenerator::CreateNormalCube(float width, float height, float depth, OUT std::vector<PosNormal>& vertices, OUT std::vector<UINT>& indices)
{
	PosNormal v[24];

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	// Fill in the front face vertex data.
	v[0] = PosNormal(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f);
	v[1] = PosNormal(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f);
	v[2] = PosNormal(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f);
	v[3] = PosNormal(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f);

	// Fill in the back face vertex data.
	v[4] = PosNormal(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f);
	v[5] = PosNormal(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f);
	v[6] = PosNormal(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f);
	v[7] = PosNormal(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f);

	// Fill in the top face vertex data.
	v[8] = PosNormal(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f);
	v[9] = PosNormal(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f);
	v[10] = PosNormal(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f);
	v[11] = PosNormal(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f);

	// Fill in the bottom face vertex data.
	v[12] = PosNormal(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f);
	v[13] = PosNormal(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f);
	v[14] = PosNormal(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f);
	v[15] = PosNormal(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = PosNormal(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f);
	v[17] = PosNormal(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f);
	v[18] = PosNormal(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f);
	v[19] = PosNormal(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f);

	// Fill in the right face vertex data.
	v[20] = PosNormal(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f);
	v[21] = PosNormal(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f);
	v[22] = PosNormal(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f);
	v[23] = PosNormal(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f);

	vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	indices.assign(&i[0], &i[36]);
}

void eel::MeshGenerator::CreateCube(float width, float height, float depth, OUT std::vector<PosBasic>& vertices, OUT std::vector<UINT>& indices)
{
	//
	// Create the vertices.
	//

	PosBasic v[24];

	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	// Fill in the front face vertex data.
	v[0] = PosBasic(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = PosBasic(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = PosBasic(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[3] = PosBasic(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	// Fill in the back face vertex data.
	v[4] = PosBasic(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = PosBasic(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[6] = PosBasic(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = PosBasic(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// Fill in the top face vertex data.
	v[8] = PosBasic(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	v[9] = PosBasic(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[10] = PosBasic(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[11] = PosBasic(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the bottom face vertex data.
	v[12] = PosBasic(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	v[13] = PosBasic(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[14] = PosBasic(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	v[15] = PosBasic(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// Fill in the left face vertex data.
	v[16] = PosBasic(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[17] = PosBasic(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[18] = PosBasic(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[19] = PosBasic(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	// Fill in the right face vertex data.
	v[20] = PosBasic(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[21] = PosBasic(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[22] = PosBasic(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[23] = PosBasic(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	indices.assign(&i[0], &i[36]);
}

void eel::MeshGenerator::CreateNormalSphere(float radius, UINT sliceCount, UINT stackCount, OUT std::vector<PosNormal>& vertices, OUT std::vector<UINT>& indices)
{
	PosNormal topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f);
	PosNormal bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f);

	vertices.push_back(topVertex);

	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f*XM_PI / sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (UINT i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for (UINT j = 0; j <= sliceCount; ++j)
		{
			float theta = j*thetaStep;

			PosNormal v;

			// spherical to cartesian
			v.m_Pos.SetX(radius*sinf(phi)*cosf(theta));
			v.m_Pos.SetY(radius*cosf(phi));
			v.m_Pos.SetZ(radius*sinf(phi)*sinf(theta));

			v.m_Normal = v.m_Pos.Normalize();

			vertices.push_back(v);
		}
	}

	vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (UINT i = 1; i <= sliceCount; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for (UINT i = 0; i < stackCount - 2; ++i)
	{
		for (UINT j = 0; j < sliceCount; ++j)
		{
			indices.push_back(baseIndex + i*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < sliceCount; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}
}