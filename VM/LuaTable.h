#pragma once
#include "LuaValue.h"
#include "Ptr.h"
class LuaTable : public LuaValue {
  public:
    typedef LuaValue base;
  public:
    LuaTable(lua_State* state, int reference);
    ~LuaTable();
  public:

    void SetValue(const char* key, Ptr<LuaTable> value);
    template<typename T> void SetValue(const char* key, T value) {
        this->_pushthis();
        this->_pushvalue(value);
        this->_setkeyvalue(key);
        this->_clear();
    }
    void SetMetatable( Ptr<LuaTable> meta);
};

