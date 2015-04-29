#include "director.h"
#include "base/renderer.h"

USING_NS_EEL;

void Director::GameLoop()
{
	//TODO : Update

	Renderer::GetInstance()->Render(m_RunningScene);
}

Director::Director()
{

}

Director::~Director()
{

}
