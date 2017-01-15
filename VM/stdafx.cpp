// stdafx.cpp : 只包括标准包含文件的源文件
// LuaT.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用


std::string LuaToString(lua_State* state_, int i) {
    LuaType type = (LuaType)lua_type(state_, i);
    string ret;
    char buffer[256];
    switch (type) {
    case LuaType::TNONE:
        sprintf_s(buffer, "%s",  "None");
        break;
    case LuaType::TNIL:
        sprintf_s(buffer, "%s",  "nil");
        break;
    case LuaType::TBOOLEAN:
        sprintf_s(buffer, "%s", lua_toboolean(state_, i) ? "true" : "false");
        break;
    case LuaType::TLIGHTUSERDATA:
        sprintf_s(buffer, "0X%08X(lightUserData)", (unsigned int)lua_touserdata(state_, i));
        break;
    case LuaType::TNUMBER:
        sprintf_s(buffer, "%lf", (double)lua_tonumber(state_, i));
        break;
    case LuaType::TSTRING:
        sprintf_s(buffer, "\"%s\"", lua_tostring(state_, i));
        break;
    case LuaType::TTABLE:
        sprintf_s(buffer, "0X%08X(table)", (unsigned int)lua_topointer(state_, i));
        break;
    case LuaType::TFUNCTION:
        sprintf_s(buffer, "0X%08X(function)", (unsigned int)lua_topointer(state_, i));
        break;
    case LuaType::TUSERDATA:
        sprintf_s(buffer, "0X%08X(userData)", (unsigned int)lua_touserdata(state_, i));
        break;
    case LuaType::TTHREAD:
        sprintf_s(buffer, "0X%08X(thread)", (unsigned int)lua_topointer(state_, i));
        break;
    default:
        break;
    }
    return buffer;
}