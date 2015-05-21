# macro

this file define macro, alias.

## file

src/base/macro.h

### macro

#### NS_EEL_BEGIN

```C++
#define NS_EEL_BEGIN namespace eel{
```

this macro define eel's namespace beginning. it prevent indent depth too deep.

#### NS_EEL_END

```C++
#define NS_EEL_END }
```

this macro define eel's namespace ending.

#### USING_NS_EEL

```C++
#define USING_NS_EEL using namespace eel;
```

#### SAFE_DELETE

```C++
//skip backslash(\)
#define SAFE_DELETE(PTR)		
{								
    if (PTR != nullptr)				
	{							
	   delete PTR;					
	   PTR = nullptr;				
	}							
}
```

safe delete pointer.

#### SAFE_RELEASE

```C++
//skip backslash(\)
#define SAFE_RELEASE(PTR)		
{								
    if (PTR != nullptr)				
	{							
	   PTR->Release();				
	   PTR = nullptr;				
	}							
}
```

safe release pointer.

#### GETTER, GETTER_REF

```C++
//skip backslash(\)
#define GETTER(type, val, func)
type Get ## func ## () const { return val; }

#define GETTER_REF(type, val, func)
const type& Get ## func ##() const { return val; }
```

it create getter member function. GETTER return by value, GETTER_REF return by reference(const T&).

#### SETTER, SETTER_REF

```C++
//skip backslash(\)
#define SETTER(type, val, func)
void Set ## func ## (type arg) { val = arg; }

#define SETTER_REF(type, val, func)
void Set ## func ## (const type& arg) { val = arg; }
```

it create setter member function. SETTER pass by value, SETTER_REF pass by reference(const T&).

#### PROPERTY, PROPERTY_REF

```C++
//skip backslash(\)
#define PROPERTY(type, name)
public:
	GETTER(type,m_ ## name, name)
	SETTER(type,m_ ## name, name)
private:
    type m_ ## name;

#define PROPERTY_REF(type, name)
public:
	GETTER_REF(type, m_ ## name, name)
	SETTER_REF(type, m_ ## name, name)
private:
	type m_ ## name;
```

it create member variable and getter / setter function automatically. it must be placed in 'private' area. member variable name is m_(name)  >> (name) is PROPERTY's second parameter. PROPERTY_REF make getter/ setter reference version(GETTER_REF, SETTER_REF).

#### READ_ONLY

```C++
//skip backslash(\)
#define READ_ONLY(type, name)
public:
	GETTER(type, m_ ## name, name)
private:
	type m_ ## name;

#define READ_ONLY_REF(type, name)
public:
	GETTER_REF(type, m_ ## name, name)
private:
	type m_ ## name;
```

it create member variable and getter function automatically. it must be placed in 'private' area. member variable name is m_(name)  >> (name) is READ_ONLY's second parameter. READ_ONLY_REF make getter reference version(GETTER_REF).

#### WRITE_ONLY

```C++
//skip backslash(\)
#define WRITE_ONLY(type, name)
public:
	SETTER(type, m_ ## name, name)
private:
	type m_ ## name;

#define WRITE_ONLY_REF(type, name)
public:
	SETTER_REF(type, m_ ## name, name)
private:
	type m_ ## name;
```

it create member variable and setter function automatically. it must be placed in 'private' area. member variable name is m_(name)  >> (name) is WRITE_ONLY's second parameter. WRITE_ONLY_REF make setter reference version(SETTER_REF).

### alias

```C++
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
```

it's alias to std's type.