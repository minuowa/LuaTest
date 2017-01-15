// Execute.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "DAssert.h"
int main() {

    const char* kBuffer = "ID=100\n"
                          "Name = 'FFF'\n"
                          "function OnOpenLua(id)\n"
                          "	print(\"OnOpenLua\")\n"
                          "	print(id)\n"
                          "	return 10"
                          "end\n";

    const char* kFileName = "login";

    {
        VirtualMachine vm;
        vm.Open();
        auto gt = vm.DoString( kBuffer);
        auto fun = vm.GetFunction("OnOpenLua");
        auto ret = fun->Call<int>();
    }

    return 0;
}

