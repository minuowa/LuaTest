// Execute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DAssert.h"
int main() {
    const char* kBuffer =
        "\
function Main(id)\n\
	print(\"MainXXX\",id)\n\
end\n\
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
            auto fun = vm.GetFunction("Main");
            fun->Call(6);
            fun = vm.GetFunction("OnOpenLua");
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

    return 0;
}

