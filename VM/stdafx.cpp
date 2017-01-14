// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// LuaT.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H �������κ�����ĸ���ͷ�ļ���
//�������ڴ��ļ�������


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