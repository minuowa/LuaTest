#pragma once
#include "Ptr.h"

namespace Lua {
class LuaTable;

class BaseValue {
  public:
    BaseValue(lua_State* state, int reference);
    virtual ~BaseValue();
  public:
    lua_State* GetState() const;
    const int GetReferenceCount() const;
    int DecReference();
    int AddReference();

    void PrintAddress();
    virtual void Print(const char* tag = nullptr);
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
    void _call(int argcount, int retcount);
    int _type();

    template<typename T = void> T _return() { }

    template<> void _return() {
    }
    template<> int _return() {
        return (int)_return<lua_Number>();
    }

    template<> unsigned int _return() {
        return (unsigned int)_return<lua_Number>();
    }

    template<> float _return() {
        return (float)_return<lua_Number>();
    }

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
};


