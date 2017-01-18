#include "stdafx.h"
#include "CallBack.h"
#include "Function.h"
#include "LuaTable.h"

namespace Lua {
CallBack::CallBack(Pointer<Function> func)
    : lua_function_(func) {

}

CallBack::CallBack()
    : lua_function_(nullptr) {

}

void CallBack::ClearReference() {
    if (lua_function_.Valid())
        lua_function_.RemoveReference();
}

}


