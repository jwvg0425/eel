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

#define GETTER(type, val, func)\
type Get ## func ## () { return val; }

#define SETTER(type, val, func)\
void Set ## func ## (type arg) { val = arg; }

//must placed in 'private' area.
//make getter, setter function and member variable automatically.
//member variable name is m_(name)  >> (name) is PROPERTY's second parameter.
#define PROPERTY(type, name)\
public:\
	GETTER(type,m_ ## name, name)\
	SETTER(type,m_ ## name, name)\
private:\
	type m_ ## name;

//must placed in 'private' area.
//make getter function and member variable automatically.
//member variable name is m_(name) >> (name) is PROPERTY's second parameter.
#define READ_ONLY(type, name)\
public:\
	GETTER(type, m_ ## name, name)\
private:\
	type m_ ## name;

//must placed in 'private' area.
//make setter function and member variable automatically.
//member variable name is m_(name) >> (name) is PROPERTY's second parameter.
#define WRITE_ONLY(type, name)\
public:\
	SETTER(type, m_ ## name, name)\
private:\
	type m_ ## name;