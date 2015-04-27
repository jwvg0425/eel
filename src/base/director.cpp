#include "director.h"
#include "base/renderer.h"

USING_NS_EEL;

void Director::GameLoop()
{
	Renderer::GetInstance()->BeginFrame();
	//TODO : Renderer Update
	Renderer::GetInstance()->Render();
}

Director::Director()
{

}

Director::~Director()
{

}
