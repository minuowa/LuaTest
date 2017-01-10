#include "stdafx.h"
#include "Allocater.h"
#include <memory>

Allocater::Allocater()
{
}


Allocater::~Allocater()
{
}

void* Allocater::Allocate(void *ptr, size_t osize, size_t nsize)
{
	if (nsize == 0)
	{
		free(ptr);
		mBlockMap.erase(ptr);
		return nullptr;
	}
	else
	{
		void* p = realloc(ptr, nsize);
		mBlockMap.insert(make_pair(p, nsize));
		return p;
	}
}
