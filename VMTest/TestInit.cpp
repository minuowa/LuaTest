#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestInit) {
public:

    TEST_METHOD(TestState) {
        VirtualMachine vm;
        vm.Open();
        Assert::IsTrue(vm.GetState() != nullptr);
        vm.Close();
        Assert::IsTrue(vm.GetState() == nullptr);
    }
};
}