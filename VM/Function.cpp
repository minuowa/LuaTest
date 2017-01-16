#include "stdafx.h"
#include "Function.h"

namespace Lua {

Function::Function(lua_State* state, int reference)
    : BaseValue(state, reference) {

}

Function::~Function() {
}

}
