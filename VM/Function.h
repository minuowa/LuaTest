#pragma once
#include "BaseValue.h"
namespace Lua {
class LuaTable;
class Function : public BaseValue {
  public:
    Function(lua_State* state, int reference);
    ~Function();
  public:
    template<typename RET>
    RET CallRet() {
        this->_clear();
        this->_pushself();
        this->_call(0, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1>
    RET CallRet(T1 arg1) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_call(1, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2>
    RET CallRet(T1 arg1, T2 arg2) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_call(2, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2, typename T3>
    RET CallRet(T1 arg1, T2 arg2, T3 arg3) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_call(3, 1);
        return _return<RET>();
    }

    void Call() {
        this->_clear();
        this->_pushself();
        this->_call(0, 0);
    }

    template< typename T1>
    void Call(T1 arg1) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_call(0, 0);
    }

    template< typename T1, typename T2>
    void Call(T1 arg1, T2 arg2) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_call(0, 0);
    }

    template< typename T1, typename T2, typename T3>
    void Call(T1 arg1, T2 arg2, T3 arg3) {
        this->_clear();
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_call(0, 0);
    }
};
};

