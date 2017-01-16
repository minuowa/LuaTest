// Execute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DAssert.h"
int main() {
    VirtualMachine vm;
    vm.Open();
    Assert::IsTrue(vm.DoFile("main.lua"));

    return 0;
}

