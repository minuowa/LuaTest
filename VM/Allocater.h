#pragma once

class Allocater
{
public:
	Allocater();
	~Allocater();
private:
	map<void*, size_t> mBlockMap;
public:
	void* Allocate(void *ptr, size_t osize, size_t nsize);
};

