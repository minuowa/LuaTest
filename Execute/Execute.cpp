// Execute.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DAssert.h"
int main() {
    VirtualMachine vm;
    vm.Open();
    Assert::IsTrue(vm.DoFile("main.lua"));

    return 0;
}

