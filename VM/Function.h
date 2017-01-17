#pragma once
#include "BaseValue.h"
namespace Lua {
class Function : public BaseValue {
  public:
    Function(lua_State* state, int reference);
    ~Function();
  public:
    template<typename RET = void>
    RET Call() {
        this->_pushself();
        lua_call(state_, 0, 1);
        return _call_return<RET>(0, 1);
    }

    template<typename RET = void, typename T1>
    RET Call(T1 arg1) {
        this->_pushself();
        this->_pushvalue(arg1);
        return _call_return<RET>(1, 1);
    }

    template<typename RET = void, typename T1, typename T2>
    RET Call(T1 arg1, T2 arg2) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        return _call_return<RET>(2, 1);
    }

    template<typename RET = void, typename T1, typename T2, typename T3>
    RET Call(T1 arg1, T2 arg2, T3 arg3) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        return _call_return<RET>(3, 1);
    }

    template<typename RET = void, typename T1, typename T2, typename T3, typename T4>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_pushvalue(arg4);
        return _call_return<RET>(4, 1);
    }

    template<typename RET = void, typename T1, typename T2, typename T3, typename T4, typename T5>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_pushvalue(arg4);
        this->_pushvalue(arg5);
        return _call_return<RET>(5, 1);
    }

    template<typename RET = void>
    RET _call_return(int nargcount, int retcount) {
        this->_call(nargcount, retcount);
        return _return<RET>();
    }
    template<>
    void _call_return(int nargcount, int retcount) {
        this->_call(nargcount, 0);
    }
};
};

