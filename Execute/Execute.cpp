// Execute.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int main()
{
	VM vm;
	vm.Open();
	//vm.DoFile("main.lua");
	Ptr<LuaTable> gt = vm.Require("login");
	assert(gt->GetNumber("ID") == 100);
	assert(gt->GetString("Name") == "FFF");
	vm.Close();
	return 0;
}

