#pragma once
class Allocater;

class VM
{
private: 
	lua_State* mState;
	Allocater* mAllocater;
	lua_Reader mLoader;
public:
	VM();
	~VM();
public:
	lua_State* GetState();

	bool Open();
	void Close();

	void GC();
	int GCBitCount();
	void* Allocate(void *ptr, size_t osize, size_t nsize);

	void SetLoader(lua_Reader loader);
	bool DoFile(const char* filename);

	void PrintGCCount(const char* what = nullptr);
	void PrintError();

private:
	bool InitState();
};

