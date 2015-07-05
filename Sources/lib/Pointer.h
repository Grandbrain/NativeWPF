#include <Unknwn.h>

template<class T>
class Pointer
{
public:

	Pointer()
	{
		mPointer = nullptr;
	}

	Pointer(T* pointer)
	{
		mPointer = nullptr;

		if (pointer)
		{
			mPointer = pointer;
			mPointer->AddRef();
		}
	}

	Pointer(const Pointer<T>& pointer)
	{
		mPointer = (T*)pointer;
		if (mPointer) mPointer->AddRef();
	}

	~Pointer()
	{
		if (mPointer)
		{
			mPointer->Release();
			mPointer = nullptr;
		}
	}

public:

	operator T*() const
	{
		return mPointer;
	}

	T& operator*() const
	{
		return *mPointer;
	}

	T** operator&()
	{
		return &mPointer;
	}

	T* operator->() const
	{
		return mPointer;
	}

	bool operator!() const
	{
		return (mPointer == nullptr);
	}

	T* operator=(T* pointer)
	{
		if (IsEqual(pointer)) return mPointer;
		if (mPointer) mPointer->Release();
		if (pointer) pointer->AddRef();
		mPointer = pointer;
		return mPointer;
	}

	T* operator=(const Pointer<T>& pointer)
	{
		mPointer = (T*)pointer;
		if (mPointer) mPointer->AddRef();
		return mPointer;
	}

	void Attach(T* pointer)
	{
		if (mPointer)
		{
			mPointer->Release();
			mPointer = pointer;
		}
	}

	T* Detach()
	{
		T* pointer = mPointer;
		mPointer = nullptr;
		return pointer;
	}

	void Release()
	{
		if (mPointer)
		{
			mPointer->Release();
			mPointer = nullptr;
		}
	}

	bool IsEqual(IUnknown* pointer)
	{
		if (pointer == nullptr && mPointer == nullptr)
			return true;

		if (pointer == nullptr || mPointer == nullptr)
			return false;

		IUnknown* temp = nullptr;
		mPointer->QueryInterface(IID_IUnknown, (void**)&temp);
		bool result = (pointer == temp);
		temp->Release();
		return result;
	}

private:

	T* mPointer;
};