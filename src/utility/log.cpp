#include "log.h"

USING_NS_EEL;

void eel::DebugLogA(LPCSTR format, ...)
{
	char buf[1024];
	va_list marker;

	va_start(marker, format);
	vsprintf(buf, format, marker);

	strcat(buf, "\n");
	OutputDebugStringA(buf);
}

void eel::DebugLogW(LPCWSTR format, ...)
{
	wchar_t buf[1024];
	va_list marker;

	va_start(marker, format);
	vswprintf(buf, format, marker);

	wcscat(buf, L"\n");
	OutputDebugStringW(buf);
}
