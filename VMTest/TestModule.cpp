#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestFile) {
public:
    TEST_METHOD(TestModule) {
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

            awake->CallRet<void>(obj1);
            Assert::IsTrue(getgid->CallRet<int>(obj1) == 20);
            setgid->CallRet<void>(obj1, 15);
            Assert::IsTrue(getgid->CallRet<int>(obj1) == 15);

            Assert::IsTrue(obj2->GetNumber("ID") == 100);
            obj2->SetValue("ID", 1500);
            Assert::IsTrue(obj2->GetNumber("ID") == 1500);

            awake->CallRet<void>(obj2);
            Assert::IsTrue(getgid->CallRet<int>(obj2) == 20);
            setgid->CallRet<void>(obj2, 35);
            Assert::IsTrue(getgid->CallRet<int>(obj2) == 35);

            assert(gt->GetNumber("ID") == 100);

            Assert::IsTrue(obj1->GetNumber("ID") == 1000);
            Assert::IsTrue(obj2->GetNumber("ID") == 1500);
        }

        Assert::IsTrue(gt->GetNumber("ID") == 100);
    }

};
}