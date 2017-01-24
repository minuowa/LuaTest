#pragma once
#include "Pointer.h"
#include "CallBack.h"
namespace Lua {
class Function;
class LuaModule;

class FunctionTaker {
  public:
    FunctionTaker();
    ~FunctionTaker();

  public:
    bool Initialize(Pointer<LuaModule> module);
    void Destroy();
  public:
    CallBack Awake;
    CallBack Start;
    CallBack Update;
    CallBack OnDestroy;
};
}

