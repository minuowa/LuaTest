#pragma once
template<typename T>
class Ptr
{
private:
	T* mObject;
public: 
	Ptr(T* obj)
		:mObject(obj)
	{
		if (mObject)
			mObject->AddReference();
	}

	Ptr(Ptr<T>& ptr)
		:mObject(ptr.GetObject())
	{
		if (mObject)
			mObject->AddReference();
	}

	Ptr operator=(Ptr<T> ptr)
	{
		this->Dec();
		mObject = ptr.GetObject();
		if (mObject)
			mObject->AddReference();
	}

	T* operator->()
	{
		return mObject;
	}

	~Ptr()
	{
		this->Dec();
	}
public:
	T* GetObject()
	{
		return mObject;
	}
	bool Valid()
	{
		return mObject;
	}
private:
	void Dec()
	{
		if (mObject&&mObject->DecReference() == 0)
		{
			delete mObject;
			mObject = nullptr;
		}
	}
};

