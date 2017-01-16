#pragma once
#include "BaseValue.h"
namespace Lua {
class Function : public BaseValue {
  public:
    Function(lua_State* state, int reference);
    ~Function();
  public:
    void Call();

    template<typename RET>
    RET Call() {
        this->_pushself();
        lua_call(state_, 0, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1>
    RET Call(T1 arg1) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_call(1, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2>
    RET Call(T1 arg1, T2 arg2) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_call(2, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2, typename T3>
    RET Call(T1 arg1, T2 arg2, T3 arg3) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_call(3, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2, typename T3, typename T4>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_pushvalue(arg4);
        this->_call(4, 1);
        return _return<RET>();
    }

    template<typename RET, typename T1, typename T2, typename T3, typename T4, typename T5>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
        this->_pushself();
        this->_pushvalue(arg1);
        this->_pushvalue(arg2);
        this->_pushvalue(arg3);
        this->_pushvalue(arg4);
        this->_pushvalue(arg5);
        this->_call(5, 1);
        return _return<RET>();
    }
};
};

