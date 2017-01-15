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
};
};

