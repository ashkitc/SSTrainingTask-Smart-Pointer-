#include <iostream>
#include <conio.h>
template <typename TYPE>
class SHSmartPtr
{
public:
	SHSmartPtr() // default constructor
	{
		storedObject = new TYPE(0);
		referenceCounter = new int(1);
	}
		explicit SHSmartPtr(TYPE *pointerToStore) //Constructor for wrap something in smart poiter
	{
		storedObject = pointerToStore;
		referenceCounter = new int(1); //when new object created it's reference count = 1
	}
	virtual ~SHSmartPtr(); //destructor for clean the memory
	 TYPE* operator -> () { return  storedObject; };
	 TYPE& operator * (){ return *storedObject; };
	//Copy constructors
 SHSmartPtr(const SHSmartPtr &anotherSmartPtr);
	operator bool()const { return storedObject != NULL; }
	//Assignment operator
	SHSmartPtr<TYPE>& operator= (const SHSmartPtr<TYPE>& anotherSmartPtr);
private:
	TYPE *storedObject; //Pointer to object wrapped in smart pointer
    int *referenceCounter; // increments in copy constructor and assignment operator, decrements in destructor
	void finalize();
};

template <typename TYPE>
SHSmartPtr<TYPE>::~SHSmartPtr()
{	
	if(storedObject)
	{
		finalize();
	}
}

template <typename TYPE>
void SHSmartPtr<TYPE>::finalize()
{
	 --( *referenceCounter ); //Decrements referenceCount
		if(*referenceCounter == 0) //And if it equals zero
		{
			cout << "Now reference count in object "<<*storedObject<<" is zero. Object'll be destroyed" <<endl;	
			if(storedObject!= NULL){
				delete storedObject; //destroy the object
			}
			delete referenceCounter;
		}
}
template <typename TYPE>
SHSmartPtr<TYPE>::SHSmartPtr(const SHSmartPtr &anotherSmartPtr)
{
	storedObject = anotherSmartPtr.storedObject;
	referenceCounter = anotherSmartPtr.referenceCounter;
	++ ( *referenceCounter ); //Copy constructor must increment reference counter
}


template <typename TYPE>
SHSmartPtr<TYPE>& SHSmartPtr<TYPE>::operator=(const SHSmartPtr &anotherSmartPtr)
{ 
	if(anotherSmartPtr)
	{
		finalize();
		storedObject = anotherSmartPtr.storedObject; //Copy data from another object
	    referenceCounter = anotherSmartPtr.referenceCounter; 
		++ ( *referenceCounter ); //Copy constructor must increment reference counter
	} else 	
	{ 
		if(*referenceCounter == 1)
		{
			finalize();
		} else
		{
			storedObject = NULL;  //nullify stored object
			--( *referenceCounter ); //decrement reference count
		}
	}
		return *this;
}
