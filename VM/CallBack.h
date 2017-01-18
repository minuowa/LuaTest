#pragma once
#include "Pointer.h"
namespace Lua {
class Function;
class CallBack {
  public:
    CallBack();
    CallBack(Pointer<Function> func);
    void ClearReference();

    inline bool Valid() const {
        return lua_function_.Valid();
    }
  public:
    template<typename RET = void, typename T1>
    RET Call(T1 arg1) {
        if (lua_function_.Valid())
            return lua_function_->Call(arg1);
        else
            return _return_valid<RET>();
    }
    template<typename RET = void, typename T1, typename T2>
    RET Call(T1 arg1, T2 arg2) {
        if (lua_function_.Valid())
            return lua_function_->Call(arg1, arg2);
        else
            return _return_valid<RET>();
    }
    template<typename RET = void, typename T1, typename T2, typename T3>
    RET Call(T1 arg1, T2 arg2, T3 arg3) {
        if (lua_function_.Valid())
            return lua_function_->Call(arg1, arg2, arg3);
        else
            return _return_valid<RET>();
    }

    template<typename RET = void, typename T1, typename T2, typename T3, typename T4>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
        if (lua_function_.Valid())
            return lua_function_->Call(arg1, arg2, arg3, arg4);
        else
            return _return_valid<RET>();
    }
    template<typename RET = void, typename T1, typename T2, typename T3, typename T4, typename T5>
    RET Call(T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
        if (lua_function_.Valid())
            return lua_function_->Call(arg1, arg2, arg3, arg4, arg5);
        else
            return _return_valid<RET>();
    }

  private:
    template<typename RET = void>
    RET _return_valid() {
        return RET(0);
    }
    template<>
    void _return_valid() {
    }
  private:
    Pointer<Function> lua_function_;
};
}

