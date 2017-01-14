#pragma once
#include "Ptr.h"
class LuaTable;

class LuaValue {
  public:
    LuaValue(lua_State* state, int reference);
    virtual ~LuaValue();
  public:
    lua_State* GetState() const;
    const int GetReferenceCount() const;
    int DecReference();
    int AddReference();

    void PrintAddress();
    virtual void Print();
    lua_Number GetNumber(const char* key);
    string GetString(const char* key);
  protected:
    void _setkeyvalue(const char* key);
    void _pushself();
    void _getkey(const char* name);
    void _pushvalue(const char* value);
    void _pushvalue(lua_Number value);
    void _pushvalue(Ptr<LuaTable> value);
    void _clear();
    void _set_meta();

    int _type();
    template<typename T> T _return() { }
    template<> lua_Number _return() {
        auto ret = lua_tonumber(state_, -stack_count_);
        return ret;
    }
    template<> const char* _return() {
        auto ret = lua_tostring(state_, -stack_count_);
        return ret;
    }
  protected:
    lua_State* state_;
  private:
    int reference_;
    int lua_reference_;
    static int stack_count_;
};

