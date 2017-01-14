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

    const char* kPrintRegist = "\
	for k,v in pairs(debug.getregistry()) do\
		print(k, v)\
    end\
	print('----------------')\
";

    const char* kFileName = "login";

    VirtualMachine vm;
    vm.Open();
    {
        vm.Require(kBuffer, kFileName);

        LuaComponent com;
        com.filename = kFileName;
        Assert::IsTrue(com.Initialize());
        vm.DoString(kPrintRegist);
        Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 1);
        com.OnDestroy();
        Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 0);

        //vm.GC();
        //vm.PrintGCCount("Closesss");
    }
    vm.GetModuleManager().Destroy();
    vm.UnloadModule(kFileName);
    vm.DoString(kPrintRegist);

    /*   vm.GC();
    vm.GC();
    vm.GC();
    vm.GC();
    vm.GC();
    vm.GC();*/
    vm.PrintGCCount("Closesss");
    return 0;
}

