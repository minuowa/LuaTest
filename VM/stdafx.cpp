// stdafx.cpp : 只包括标准包含文件的源文件
// LuaT.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用


void PrintLuaValue(lua_State* state_, int i) {
    LuaType type = (LuaType)lua_type(state_, i);
    switch (type) {
    case LuaType::TNONE:
        printf("(%d)(None):%s", i, "None");
        break;
    case LuaType::TNIL:
        printf("(%d)(Null):%s", i, "nil");
        break;
    case LuaType::TBOOLEAN:
        printf("(%d)(Bool):%s", i, lua_toboolean(state_, i) ? "true" : "false");
        break;
    case LuaType::TLIGHTUSERDATA:
        printf("(%d)(LightUserData):0X%08X", i, lua_touserdata(state_, i));
        break;
    case LuaType::TNUMBER:
        printf("(%d)(Number):%d", i, lua_tonumber(state_, i));
        break;
    case LuaType::TSTRING:
        printf("(%d)(String):%s", i, lua_tostring(state_, i));
        break;
    case LuaType::TTABLE:
        printf("(%d)(Table):0X%08X", i, (int)lua_topointer(state_, i));
        break;
    case LuaType::TFUNCTION:
        printf("(%d)(Function):0X%08X", i, (int)lua_topointer(state_, i));
        break;
    case LuaType::TUSERDATA:
        printf("(%d)(UserData):0X%08X", i, (int)lua_topointer(state_, i));
        break;
    case LuaType::TTHREAD:
        printf("(%d)(Thread):0X%08X", i, (int)lua_topointer(state_, i));
        break;
    default:
        break;
    }
    endl(std::cout);
}