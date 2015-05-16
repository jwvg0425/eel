# application

application is a singleton class that encapsulates program window.

this class handle window messages and manage window data(size, caption, etc..).

## file

src/base/application.h  
src/base/application.cpp

##define

```C++
class Application : public Object
```

### member types

### member functions

#### GetInstance

```C++
static Application* GetInstance()
```

this static member function return application's instance.

#### WndProc

```C++
virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
```

this member function is callback function. it handle window messages. if you want to modify WndProc's work, you could override this function. but this function is very important to run program. therefore **DON'T override** this function unless you know what you are doing.

#### Run

```C++
int Run()
```

this function start game loop & windows message loop. this function return program's exit code.

#### Init

```C++
bool Init(std::wstring title, int width, int height)
```

this function init and create program window. if failed to init program, return false.

#### GetAspectRatio

```C++
float GetAspectRatio() const
```

this function return program window's aspect ratio.

#### FinishLaunching

```C++
virtual void FinishLaunching()
````

this function called when program start(complete to create program window). you should override this function and init state depending on your game's feature.

### non-member functions

### example