// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#ifdef __cplusplus
extern "C" {
#endif

#include "lstate.h"
#include "lgc.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif

#include <math.h>

#pragma comment(lib, "lua51.lib")

#define SAFE_DELETE(b) {delete(b);b=nullptr;}

#include <list>
#include <map>
#include <string>
using namespace std;
#include <assert.h>
#include <iostream>
#include "Fun.h"

enum LuaType {
    TNONE = (-1)
    , TNIL
    , TBOOLEAN
    , TLIGHTUSERDATA
    , TNUMBER
    , TSTRING
    , TTABLE
    , TFUNCTION
    , TUSERDATA
    , TTHREAD
};
string LuaToString(lua_State* state_, int i);

