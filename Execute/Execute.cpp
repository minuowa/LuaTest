// Execute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DAssert.h"

int main() {

    const char* kBuffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";

    const char* kFileName = "login";

    {
        VirtualMachine vm;
        vm.Open();
        auto gt = vm.Require(kBuffer, kFileName);

        LuaComponent com;
        com.virtual_machine = &vm;
        com.filename = kFileName;


        Assert::IsTrue(com.Initialize());
        vm.PrintTable(gt);

        Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 2);
        com.OnDestroy();
        Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 1);
        vm.GetModuleManager().Destroy();
        Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 1);
    }

    return 0;
}

