#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestModuleManager) {
public:

    TEST_METHOD(Test) {

        const char* kBuffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";



        const char* kFileName = "login";

        {
            VirtualMachine vm;
            vm.Open();
            vm.Require(kBuffer, kFileName);

            LuaComponent com;
            com.virtual_machine = &vm;
            com.filename = kFileName;

            Assert::IsTrue(com.Initialize());
            Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 2);
            com.OnDestroy();
            Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 1);
            vm.GetModuleManager().Destroy();
            Assert::IsTrue(com.GetLuaInstance()->GetReferenceCount() == 1);
        }
    }
};
}