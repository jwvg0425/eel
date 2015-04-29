#include "d3dx11Effect.h"
#include <dxerr.h>

//debug - memory tracing
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)													\
{																\
	HRESULT hr = (x);											\
if (FAILED(hr))												\
	{															\
	DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);		\
	}															\
}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif
#endif