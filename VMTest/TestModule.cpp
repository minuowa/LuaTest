#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestFile) {
public:
    const char* buffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";
    TEST_METHOD(TestModule) {
        VirtualMachine vm;
        vm.Open();
        Ptr<LuaTable> gt = vm.Require(buffer, "login");
        assert(gt->GetNumber("ID") == 100);
        assert(gt->GetString("Name") == "FFF");

        {
            Ptr<LuaTable> obj1 = vm.GetModuleManager().CreateInstance("login");
            Ptr<LuaTable> obj2 = vm.GetModuleManager().CreateInstance("login");

            Assert::IsTrue(obj1->GetNumber("ID") == 100);
            Assert::IsTrue(obj1->GetString("Name") == "FFF");

            Assert::IsTrue(obj2->GetNumber("ID") == 100);
            Assert::IsTrue(obj2->GetString("Name") == "FFF");

            obj1->SetValue("ID", 1000);
            obj2->SetValue("ID", 1500);

            Assert::IsTrue(obj1->GetNumber("ID") == 1000);
            Assert::IsTrue(obj2->GetNumber("ID") == 1500);
        }

        Assert::IsTrue(gt->GetNumber("ID") == 100);
    }

};
}