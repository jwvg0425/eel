#include "boxLand.h"
#include "box.h"

BoxLand* GBoxLand = nullptr;

BoxLand::BoxLand(eel::Vector3 boxSize)
	:m_BoxSize(boxSize)
{
	float totalWidth = boxSize.GetX() * WIDTH_BOX_NUM;
	float totalDepth = boxSize.GetZ() * DEPTH_BOX_NUM;

	float halfWidth = totalWidth / 2;
	float halfDepth = totalDepth / 2;

	m_GridOrigin.SetX(-halfWidth);
	m_GridOrigin.SetY(ZERO_HEIGHT);
	m_GridOrigin.SetZ(-halfDepth);

	auto scene = eel::Director::GetInstance()->GetRunningScene();

	for(int xIdx = 0; xIdx < WIDTH_BOX_NUM; ++xIdx)
	{
		for(int yIdx = 0; yIdx < HEIGHT_BOX_NUM; ++yIdx)
		{
			for(int zIdx = 0; zIdx < DEPTH_BOX_NUM; ++zIdx)
			{
				m_BoxStates[xIdx][yIdx][zIdx] = false;
				if(yIdx == 0)
				{
					auto box = Box::Create(boxSize);
					float posX = m_GridOrigin.GetX() + xIdx*m_BoxSize.GetX();
					float posY = m_GridOrigin.GetY() - m_BoxSize.GetY();
					float posZ = m_GridOrigin.GetZ() + zIdx*m_BoxSize.GetZ();
					box->SetPosition(posX, posY, posZ);
					scene->AddChild(box);
				}
			}
		}
	}

}

BoxLand::~BoxLand()
{
}

void BoxLand::SetBoxState(eel::Vector3 position, bool state)
{
	if(!IsInTheLand(position))
	   return;

	m_BoxStates[position.GetX()][position.GetY()][position.GetZ()] = state;
}

void BoxLand::AddBox(eel::Vector3 position)
{
	if(!IsInTheLand(position))
		return;

	auto box = Box::Create(m_BoxSize);
	auto pos = GetRealPos(position);
	box->SetPosition(pos.GetX(), pos.GetY(), pos.GetZ());
	auto scene = eel::Director::GetInstance()->GetRunningScene();
	scene->AddChild(box);
}

bool BoxLand::IsInTheLand(eel::Vector3 position)
{
	return !( position.GetX() < 0 || position.GetX() > WIDTH_BOX_NUM
			|| position.GetY() < 0 || position.GetY() > HEIGHT_BOX_NUM
			|| position.GetZ() < 0 || position.GetZ() > DEPTH_BOX_NUM );
}

eel::Vector3 BoxLand::GetRealPos(eel::Vector3 gridPos)
{
	eel::Vector3 pos;
	pos.SetX(gridPos.GetX()*m_BoxSize.GetX() + m_GridOrigin.GetX());
	pos.SetY(gridPos.GetY()*m_BoxSize.GetY() + m_GridOrigin.GetY());
	pos.SetZ(gridPos.GetZ()*m_BoxSize.GetZ() + m_GridOrigin.GetZ());

	return pos;
}

eel::Vector3 BoxLand::GetGridPos(eel::Vector3 realPos)
{
	eel::Vector3 pos;

	pos.SetX(( realPos.GetX() - m_GridOrigin.GetX() ) / m_BoxSize.GetX());
	pos.SetY(( realPos.GetY() - m_GridOrigin.GetY() ) / m_BoxSize.GetY());
	pos.SetZ(( realPos.GetZ() - m_GridOrigin.GetZ() ) / m_BoxSize.GetZ());

	return pos;
}

float BoxLand::UpperLimit(eel::Vector3 realPos)
{
	auto gridPos = GetGridPos(realPos);
	int x = gridPos.GetX();
	int y = gridPos.GetY();
	int z = gridPos.GetZ();

	int endY = y;
	float halfHeight = m_BoxSize.GetY() / 2;
	for(int yIdx = y; yIdx < HEIGHT_BOX_NUM; ++yIdx)
	{
		if(m_BoxStates[x][yIdx][z])
		{
			endY = yIdx;
			return endY*m_BoxSize.GetY() + m_GridOrigin.GetY() - halfHeight;
		}
	}
	return HEIGHT_BOX_NUM*m_BoxSize.GetY() + m_GridOrigin.GetY() - halfHeight;
}

float BoxLand::LowerLimit(eel::Vector3 realPos)
{
	auto gridPos = GetGridPos(realPos);
	float halfHeight = m_BoxSize.GetY() / 2;

	if(!IsInTheLand(gridPos))
	{
		return m_GridOrigin.GetY() + halfHeight;
	}
	int x = gridPos.GetX();
	int y = gridPos.GetY();
	int z = gridPos.GetZ();

	int endY = y;
	for(int yIdx = y; yIdx > 0 ; --yIdx)
	{
		if(m_BoxStates[x][yIdx][z])
		{
			endY = yIdx;
			return endY*m_BoxSize.GetY() + m_GridOrigin.GetY() + halfHeight;
		}
	}
	return m_GridOrigin.GetY() + halfHeight;
}
