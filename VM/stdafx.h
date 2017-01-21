// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件

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

