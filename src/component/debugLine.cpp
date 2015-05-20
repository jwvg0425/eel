#include "debugLine.h"
#include "render\vertex\posColor.h"
#include "base\renderer.h"
#include "base\director.h"
#include "component\scene.h"

eel::DebugLine::DebugLine()
{
	Point3 pos1 = Point3(0.f, 0.f, 0.f);
	Point3 pos2 = Point3(0.f, 0.f, 100.f);
	DebugLine(pos1, pos2);
}

eel::DebugLine::DebugLine(const Ray& ray)
{
	auto origin = ray.GetRayOrigin();
	auto dir = ray.GetRayDirection();
	Point3 pos1 = Point3(origin.GetX(), origin.GetY(), origin.GetZ());
	Point3 pos2 = Point3(dir.GetX()*100.f, dir.GetY()*100.f, dir.GetZ()*100.f);
	DebugLine(pos1, pos2);
}



eel::DebugLine::DebugLine(const Point3& pos1, const Point3& pos2)
{
	Color4 color {0.f, 0.f, 0.f, 1.f};
	DebugLine(pos1, pos2, color);
}

eel::DebugLine::DebugLine(const Point3& pos1, const Point3& pos2, const Color4& color)
{
	std::vector<PosColor> vertex {PosColor(pos1, color), PosColor(pos2, color)};
	std::vector<UINT> index {0, 1};
	m_Model = Model::Create(vertex, index);
	m_Model->SetTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	m_Model->SetEffect(Renderer::GetInstance()->GetEffect("SimpleColor"));
	
	auto scene = Director::GetInstance()->GetRunningScene();
	scene->AddChild(m_Model);
}

eel::DebugLine::~DebugLine()
{
	auto scene = Director::GetInstance()->GetRunningScene();
	scene->RemoveChild(m_Model);
}
