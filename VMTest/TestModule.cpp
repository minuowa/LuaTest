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
        Pointer<LuaTable> gt = vm.Require(kFileName, buffer);
        assert(gt->GetNumber("ID") == 100);

        {
            Component com1, com2;
            com1.filename = kFileName;
            com2.filename = kFileName;
            com1.virtual_machine = &vm;
            com2.virtual_machine = &vm;

            Assert::IsTrue(com1.Initialize());
            Assert::IsTrue(com2.Initialize());

            Pointer<LuaTable> obj1 = com1.GetLuaInstance();
            Pointer<LuaTable> obj2 = com2.GetLuaInstance();

            com1.Awake();

            Assert::IsTrue(obj1->GetNumber("gid") == 20);
        }

        Assert::IsTrue(gt->GetNumber("ID") == 100);
    }

};
}