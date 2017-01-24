#pragma once
#include "Pointer.h"
#include "FunctionTaker.h"
#include "LuaTable.h"
namespace Lua {
class LuaModule: public LuaTable  {
  public:
    LuaModule(lua_State* state, int reference, const char* name);
    ~LuaModule();
  public:
    int GetModuleReferenceCount();
    void SetModuleReferenceCount(int count);
  private:
    string name_;
};
};

