// Execute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DAssert.h"
#include "Mode.h"

int main() {

    int a = getMode<int>();
    getMode();
    const char* buffer = "\
module(...,package.seeall)\n\
ID=100\n\
\
function _M:Awake()\n\
	self.gid=20\n\
	print('Awake', self.gid)\n\
end\n\
function _M:GetGID()\n\
	return self.gid\n\
end\n\
function _M:SetGID(id)\n\
	self.gid=id\n\
end\n\
                         ";

    const char* kFileName = "login";

    VirtualMachine vm;
    vm.Open();
    Ptr<LuaTable> gt = vm.Require(kFileName, buffer);
    assert(gt->GetNumber("ID") == 100);

    {
        Ptr<LuaTable> obj1 = vm.GetModuleManager().CreateInstance(kFileName);
        Ptr<LuaTable> obj2 = vm.GetModuleManager().CreateInstance(kFileName);

        auto awake = gt->GetFunction("Awake");
        auto getgid = gt->GetFunction("GetGID");
        auto setgid = gt->GetFunction("SetGID");

        Assert::IsTrue(obj1->GetNumber("ID") == 100);
        obj1->SetValue("ID", 1000);
        Assert::IsTrue(obj1->GetNumber("ID") == 1000);

        awake->Call(obj1);
        Assert::IsTrue(getgid->CallRet<int>(obj1) == 20);
        setgid->Call(obj1, 15);
        Assert::IsTrue(getgid->CallRet<int>(obj1) == 15);

        Assert::IsTrue(obj2->GetNumber("ID") == 100);
        obj2->SetValue("ID", 1500);
        Assert::IsTrue(obj2->GetNumber("ID") == 1500);

        awake->Call(obj2);
        Assert::IsTrue(getgid->CallRet<int>(obj2) == 20);
        setgid->Call(obj2, 35);
        Assert::IsTrue(getgid->CallRet<int>(obj2) == 35);

        assert(gt->GetNumber("ID") == 100);

        Assert::IsTrue(obj1->GetNumber("ID") == 1000);
        Assert::IsTrue(obj2->GetNumber("ID") == 1500);
    }

    Assert::IsTrue(gt->GetNumber("ID") == 100);
    vm.PrintDebugRegistry();
    return 0;
}

