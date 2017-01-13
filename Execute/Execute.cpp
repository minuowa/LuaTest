// Execute.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	const char* buffer = "\
				module(...,package.seeall)\
				ID=100\
				Name='FFF'\
				";

	VM vm;
	vm.Open();
	Ptr<LuaTable> gt = vm.Require(buffer, "login");
	//Ptr<LuaTable> gt = vm.Require("login");
	assert(gt->GetNumber("ID") == 100);
	assert(gt->GetString("Name") == "FFF");
	return 0;
}

