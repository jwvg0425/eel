#include "base/macro.h"

NS_EEL_BEGIN

template<typename T>
bool Equal(T a, T b)
{
	return a == b;
}

template<typename T>
bool NotEqual(T a, T b)
{
	return a != b;
}

template<typename T>
bool More(T a, T b)
{
	return a > b;
}

template<typename T>
bool Less(T a, T b)
{
	return a < b;
}

template<typename T>
bool MoreEqual(T a, T b)
{
	return a >= b;
}

template<typename T>
bool LessEqual(T a, T b)
{
	return a <= b;
}

NS_EEL_END