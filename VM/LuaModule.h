#pragma once
#include "LuaTable.h"
#include "Ptr.h"
class LuaModule {
  public:
    LuaModule(const char* name,Ptr<LuaTable> luaValue);
    ~LuaModule();
  private:
    string mName;
    Ptr<LuaTable> mLuaValue;
};

