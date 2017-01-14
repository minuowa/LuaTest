#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestModuleManager) {
public:

    TEST_METHOD(Test) {

        const char* buffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";
        const char* kFileName = "login";

        VirtualMachine vm;
        vm.Open();
        vm.Require(buffer, "login");

        {
            LuaComponent com;
            com.filename = kFileName;
            Assert::IsTrue(com.Initialize());
            com.OnDestroy();
        }
    }
};
}