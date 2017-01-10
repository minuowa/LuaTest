#include "stdafx.h"
#include "Allocater.h"
#include <memory>

Allocater::Allocater()
	:mSize(0)
{
}


Allocater::~Allocater()
{
	assert(mSize == 0);
}

void* Allocater::Allocate(void *ptr, size_t osize, size_t nsize)
{
	if (nsize == 0)
	{
		this->Remove(ptr, true);
		return nullptr;
	}
	else
	{
		if (ptr != nullptr)
			this->Remove(ptr, false);

		void* p = realloc(ptr, nsize);
		mBlockMap.insert(make_pair(p, nsize));
		mSize += nsize;
		return p;
	}
}

void Allocater::Remove(void* ptr,bool destroy)
{
	auto iter = mBlockMap.find(ptr);
	if (iter != mBlockMap.end())
	{
		mSize -= iter->second;
		mBlockMap.erase(iter);
		if (destroy)
			free(ptr);
		ptr = nullptr;
	}
}
