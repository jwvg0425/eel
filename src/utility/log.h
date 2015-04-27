#pragma once
#include <Windows.h>
#include "base/macro.h"


NS_EEL_BEGIN

#ifdef UNICODE
#define LOG(format, ...) DebugLogW(format, __VA_ARGS__)
#else
#define LOG(format, ...) DebugLogA(format, __VA_ARGS__)
#endif

void DebugLogA(LPCSTR format, ...);
void DebugLogW(LPCWSTR format, ...);

NS_EEL_END