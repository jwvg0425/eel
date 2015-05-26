#include "mousePickTriangleEvent.h"

eel::MousePickTriangleEvent::MousePickTriangleEvent(int triangleIdx, float dist, Point3 mousePos)
	:m_TriangleIdx(triangleIdx), m_Distance(dist), m_MousePos(mousePos)
{

}
