#pragma once
#include "LuaValue.h"
#include "Ptr.h"
class LuaTable : public LuaValue {
  public:
    LuaTable(lua_State* state, int reference);
    ~LuaTable();
  public:
    void Print();
    void SetValue(const char* name, lua_Number value);
    void SetValue(const char* name, const char* value);
    void SetValue(const char* name, Ptr<LuaTable> value);
};

