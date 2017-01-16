#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest {
TEST_CLASS(TestGlobalFunction) {
public:

    TEST_METHOD(GlobalFunction) {

        const char* kBuffer =
            "\
function OnOpenLua(id)\n\
	print(\"OnOpenLua\")\n\
	print(id)\n\
	return id\n\
end\n\
function OnOpenLua5(id1, id2, id3, id4, id5)\n\
    print(\"OnOpenLua5\",id1,id2,id3,id4,id5)\n\
	return id1+id2+id3+id4+id5\n\
end\n\
";

        const char* kFileName = "login";

        {
            VirtualMachine vm;
            vm.Open();
            auto gt = vm.DoString(kBuffer);
            {
                auto fun = vm.GetFunction("OnOpenLua");
                auto ret = fun->Call<int>(5);
                Assert::IsTrue(ret == 5);

                ret = fun->Call<int>(6);
                Assert::IsTrue(ret == 6);

                ret = fun->Call<int>(5, 6);
                Assert::IsTrue(ret == 5);
            }
            {
                auto fun = vm.GetFunction("OnOpenLua5");
                auto ret = fun->Call<int>(1, 2, 3, 4, 5);
                Assert::IsTrue(ret == 15);
            }

        }
    }
};
}