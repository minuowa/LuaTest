#pragma once

class Allocater
{
public:
	Allocater();
	~Allocater();
private:
	map<void*, size_t> mBlockMap;
	size_t mSize;
public:
	void* Allocate(void *ptr, size_t osize, size_t nsize);
private:
	void Remove(void* ptr, bool destroy);
};

