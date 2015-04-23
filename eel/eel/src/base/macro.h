#pragma once

//name space
#define NS_EEL_BEGIN namespace eel{
#define NS_EEL_END }
#define USING_NS_EEL using namespace eel;


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

#define SAFE_DELETE(PTR)		\
{								\
if (PTR != nullptr)				\
	{							\
	delete PTR;					\
	PTR = nullptr;				\
	}							\
}
#define SAFE_RELEASE(PTR)		\
{								\
if (PTR != nullptr)				\
	{							\
	PTR->Release();				\
	PTR = nullptr;				\
	}							\
}