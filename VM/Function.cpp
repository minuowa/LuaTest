#include "stdafx.h"
#include "Function.h"

namespace Lua {

Function::Function(lua_State* state, int reference)
    : BaseValue(state, reference) {

}

Function::~Function() {
}

void Function::Call() {
    this->_pushself();
    lua_call(state_, 0, 0);
}

}
