#include "boxLand.h"
#include "box.h"

BoxLand* GBoxLand = nullptr;

BoxLand::BoxLand(eel::Vector3 boxSize, int widthBoxNum, int heightBoxNum, int depthBoxNum)
	:m_BoxSize(boxSize), m_MaxXIdx(widthBoxNum), m_MaxYIdx(heightBoxNum), m_MaxZIdx(depthBoxNum)
{
	float totalWidth = boxSize.GetX() * widthBoxNum;
	float totalDepth = boxSize.GetZ() * depthBoxNum;

	float halfWidth = totalWidth / 2;
	float halfDepth = totalDepth / 2;

	m_GridOrigin.SetX(-halfWidth);
	m_GridOrigin.SetY(-100.f);
	m_GridOrigin.SetZ(-halfDepth);

	auto scene = eel::Director::GetInstance()->GetRunningScene();

	for(int xIdx = 0; xIdx < widthBoxNum; ++xIdx) for(int zIdx = 0; zIdx < depthBoxNum; ++zIdx)
	{
		auto box = Box::Create(boxSize);
		float posX = m_GridOrigin.GetX() + xIdx*m_BoxSize.GetX();
		float posY = m_GridOrigin.GetY() - m_BoxSize.GetY();
		float posZ = m_GridOrigin.GetZ() + zIdx*m_BoxSize.GetZ();
		box->SetPosition(posX, posY, posZ);
		scene->AddChild(box);
	}
}

BoxLand::~BoxLand()
{
}
