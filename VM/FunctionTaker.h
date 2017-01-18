#pragma once
#include "Pointer.h"
#include "CallBack.h"
namespace Lua {
class Function;
class LuaTable;


class FunctionTaker {
  public:
    FunctionTaker();
    ~FunctionTaker();

  public:
    bool Initialize(Pointer<LuaTable> module);
    void Destroy();
  public:
    CallBack Awake;
    CallBack Start;
    CallBack Update;
    CallBack OnDestroy;
};
}

