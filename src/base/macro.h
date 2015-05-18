#pragma once
#include <memory>
#include <array>
#include <type_traits>
#include <xtr1common>

//name space
#define NS_EEL_BEGIN namespace eel{
#define NS_EEL_END }
#define USING_NS_EEL using namespace eel;

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
type Get ## func ## () const { return val; }

#define GETTER_REF(type, val, func)\
const type& Get ## func ##() const { return val; }

#define SETTER(type, val, func)\
void Set ## func ## (type arg) { val = arg; }

#define SETTER_REF(type, val, func)\
void Set ## func ## (const type& arg) { val = arg; }

//must placed in 'private' area.
//make getter, setter function and member variable automatically.
//member variable name is m_(name)  >> (name) is PROPERTY's second parameter.
#define PROPERTY(type, name)\
public:\
	GETTER(type,m_ ## name, name)\
	SETTER(type,m_ ## name, name)\
private:\
	type m_ ## name;

#define PROPERTY_REF(type, name)\
public:\
	GETTER_REF(type, m_ ## name, name)\
	SETTER_REF(type, m_ ## name, name)\
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

#define READ_ONLY_REF(type, name)\
public:\
	GETTER_REF(type, m_ ## name, name)\
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

#define WRITE_ONLY_REF(type, name)\
public:\
	SETTER_REF(type, m_ ## name, name)\
private:\
	type m_ ## name;

//smart pointer alias
template <typename T>
using SPTR = std::shared_ptr<T>;

template <typename T>
using UPTR = std::unique_ptr<T>;

template<typename T>
using WPTR = std::weak_ptr<T>;

template<typename T, int N>
using ARRAY = std::array<T, N>;

template<typename T, int ROW, int COL>
using ARRAY2D = std::array<std::array<T, COL>, ROW>;

template<typename T, int A, int B, int C>
using ARRAY3D = std::array<std::array<std::array<T, C>, B>, A > ;

//bit macro function
template<typename T1, typename T2>
void SetBit(T1& dest, T2 bit)
{
	static_assert(std::is_integral<T1>::value, "T1, T2 must be an integral type.");
	static_assert(std::is_convertible<T2, T1>::value, "must be convertible from T2 to T1");
	dest |= bit;
}

template<typename T1, typename T2>
void RemoveBit(T1& dest, T2 bit)
{
	static_assert(std::is_integral<T1>::value, "T1 must be an integral type.");
	static_assert(std::is_convertible<T2, T1>::value, "must be convertible from T2 to T1");
	dest &= ~bit;
}


