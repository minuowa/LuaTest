#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest
{		
	TEST_CLASS(TestFile)
	{
	public:
		
		TEST_METHOD(DoFile)
		{
			VM vm;
			vm.Open();
			Assert::IsTrue(vm.DoFile("main.lua"));
		}

	};
}