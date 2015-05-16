# director

director is a singleton class that manage game state. 

## file

src/base/director.h  
src/base/director.cpp

##define

```C++
class Director : public Object, public Singleton<Director>
```

### member types

### member functions

#### GameLoop

```C++
void GameLoop()
```

this function do GameLoop(execute 1 frame). this function automatically called. so you don't need to take care of this function.

#### RunWithScene

```C++
void RunWithScene(SPTR<Scene> scene)
```

you MUST call this function at the program start(Application::FinishLaunching). if you don't call this function, program crashed. director used scene for executing GameLoop and Rendering.

#### RegisterEvent

```C++
template<typename T, typename F>
void RegisterEvent(EventType type, T* object, F memFunc)
```

this fuction register the fuction invoked when specified event occured. see [EventType](). T must be descendant of eel::Object.

#### UnregisterEvent
```C++
void UnregisterEvent(EventType type, Object* object)
```

this function unregister functions associated *object*. this function called, than clear *object*'s registered function that invoked when event of *type* occured.

#### UnregisterAllEvent

```C++
void UnregisterAllEvent(Object* object);
```

this function unregister **all** functions associated *object*.

#### ExecuteEvent

```C++
void ExecuteEvent(EventType type, const Event& e)
```

this function invoked when event of *type* occured. this function invoke all function registered by RegisterEvent. this function automatically called. so you don't need to take care of this function.

### non-member functions

### example