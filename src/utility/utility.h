#pragma once
#include "base/macro.h"

NS_EEL_BEGIN

template<typename T>
struct is_offset_exist
{
	template<typename Arg>
	static auto Fn(int)
		->decltype(Arg::offset, std::true_type());
	template<typename Arg>
	static auto Fn(...)
		->std::false_type;
	using type = decltype(Fn<T>(0));
	static const bool value = type::value;
};

NS_EEL_END