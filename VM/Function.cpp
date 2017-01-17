#include "stdafx.h"
#include "Function.h"
#include "LuaTable.h"
namespace Lua {

Function::Function(lua_State* state, int reference)
    : BaseValue(state, reference) {

}

Function::~Function() {
}

}
