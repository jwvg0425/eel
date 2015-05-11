#include <string>
#include "object.h"
#include "base/director.h"


USING_NS_EEL;

eel::Object::~Object()
{
	Director::GetInstance()->UnregisterAllEvent(this);
}
