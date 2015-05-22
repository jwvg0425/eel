#include "debugLine.h"
#include "base/director.h"
#include "render/vertex/posColor.h"
#include "base/renderer.h"


eel::DebugLine::DebugLine()
{

}

eel::DebugLine::~DebugLine()
{
	auto scene = Director::GetInstance()->GetRunningScene();
	scene->RemoveChild(m_Model);
}


void eel::DebugLine::SetLine(const Point3& pos1, const Point3& pos2, const Color4& color)
{
	std::vector<PosColor> vertex {PosColor(pos1, color), PosColor(pos2, color)};
	std::vector<UINT> index {0, 1};
	m_Model = Model::Create(vertex, index);
	m_Model->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	m_Model->SetEffect(Renderer::GetInstance()->GetEffect("SimpleColor"));

	auto scene = Director::GetInstance()->GetRunningScene();
	scene->AddChild(m_Model);
}

void eel::DebugLine::SetLine(const Vector3& pos1, const Vector3& pos2)
{
	Color4 color {0.f, 0.f, 0.f, 1.f};
	SetLine(pos1, pos2, color);
}

void eel::DebugLine::SetLine(const Ray& ray)
{

}
