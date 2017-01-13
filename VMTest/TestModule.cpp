#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest
{		
	TEST_CLASS(TestFile)
	{
	public:
		
		TEST_METHOD(TestModule)
		{
			const char* buffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";

			VM vm;
			vm.Open();
			Ptr<LuaTable> gt = vm.Require(buffer, "login");
			Assert::IsTrue(gt->GetNumber("ID") == 100);
			Assert::IsTrue(gt->GetString("Name") == "FFF");
		}

	};
}