#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VMTest
{		
	TEST_CLASS(TestInit)
	{
	public:
		
		TEST_METHOD(TestState)
		{
			VM vm;
			vm.Open();
			Assert::IsTrue(vm.GetState());
			//Assert::IsTrue(547 == vm.GCBitCount());
			vm.GC();
			//Assert::IsTrue(547 == vm.GCBitCount());
			vm.Close();
			Assert::IsFalse(vm.GetState());
		}

	};
}