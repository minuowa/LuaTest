// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

//#include "targetver.h"

// 用于 CppUnitTest 的头文件
#include "CppUnitTest.h"

// TODO: 在此处引用程序需要的其他头文件
#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#ifdef __cplusplus
}
#endif

#include <list>
#include <map>
#include <string>
using namespace std;
#include <assert.h>


#include "VirtualMachine.h"

using namespace Lua;



