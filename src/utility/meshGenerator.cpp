#include "meshGenerator.h"

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

void eel::MeshGenerator::CreateGrid(float width, float depth, int widthBoxNum, int depthBoxNum, 
									OUT std::vector<PosBasic>& vertices, OUT std::vector<UINT>& indices)
{
	UINT vertexCount = ( depthBoxNum + 1 )*( widthBoxNum + 1 );
	UINT faceCount = depthBoxNum * widthBoxNum * 2;

	float halfWidth = 0.5f*width;
	float halfDepth = 0.5f*depth;

	float dx = width / widthBoxNum;
	float dz = depth / depthBoxNum;

	float du = 1.0f / widthBoxNum;
	float dv = 1.0f / depthBoxNum;

	vertices.resize(vertexCount);
	for(int i = 0; i < depthBoxNum + 1; ++i)
	{
		float z = halfDepth - i*dz;
		for(int j = 0; j < widthBoxNum + 1; ++j)
		{
			float x = -halfWidth + j*dx;

			vertices[i*( widthBoxNum + 1 ) + j].m_Pos = eel::Vector3(x, 0.0f, z);
			vertices[i*( widthBoxNum + 1 ) + j].m_Normal = eel::Vector3(0.0f, 1.0f, 0.0f);

			// Stretch texture over grid.
			vertices[i*( widthBoxNum + 1 ) + j].m_Tex.SetX(j*du);
			vertices[i*( widthBoxNum + 1 ) + j].m_Tex.SetY(i*dv);
		}
	}

	indices.resize(faceCount * 3);

	// Iterate over each quad and compute indices.
	UINT k = 0;
	for(UINT i = 0; i < depthBoxNum; ++i)
	{
		for(UINT j = 0; j < widthBoxNum; ++j)
		{
			indices[k] = i*( widthBoxNum + 1 ) + j;
			indices[k + 1] = i*( widthBoxNum + 1 ) + j + 1;
			indices[k + 2] = ( i + 1 )*( widthBoxNum + 1 ) + j;

			indices[k + 3] = ( i + 1 )*( widthBoxNum + 1 ) + j;
			indices[k + 4] = i*( widthBoxNum + 1 ) + j + 1;
			indices[k + 5] = ( i + 1 )*( widthBoxNum + 1 ) + j + 1;

			k += 6; // next quad
		}
	}
}
