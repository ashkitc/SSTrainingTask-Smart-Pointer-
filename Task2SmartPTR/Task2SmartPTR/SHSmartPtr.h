#include <iostream>
#include <conio.h>
template <typename TYPE>
class SHSmartPtr
{
public:
	SHSmartPtr() // default constructor
	{
		storedObject = NULL;
		referenceCounter = 1;
	}
	SHSmartPtr(TYPE *pointerToStore) //Constructor for wrap something in smart poiter
	{
		storedObject = pointerToStore;
		referenceCounter = 1;
	}
	~SHSmartPtr(); //destructor for clean the memory
	inline TYPE* operator -> () { return  storedObject; };
	inline TYPE& operator * ()  { return *storedObject; };
	inline void setUpData(TYPE objectValue)
	{
		if(storedObject == NULL)
		{
			storedObject = new TYPE;
		}
		*storedObject = objectValue;
	}
	//Copy constructors
	inline SHSmartPtr(const SHSmartPtr &anotherSmartPtr);
	inline operator bool()const { return storedObject != NULL; }
	//Assignment operator
	SHSmartPtr<TYPE>& operator= (const SHSmartPtr<TYPE>& anotherSmartPtr);
private:
	TYPE *storedObject; //Pointer to object wrapped in smart pointer
    mutable unsigned int referenceCounter; // increments in copy constructor and assignment operator, decrements in destructor
};

template <typename TYPE>
SHSmartPtr<TYPE>::~SHSmartPtr()
{	
	TYPE temporaryStorage;
	if(storedObject)
	{
		temporaryStorage = *
			storedObject;
	}
	--referenceCounter; //Decrements referenceCount
	if(referenceCounter == 0) //And if it equals zero
	{
		cout << "Now reference count in object "<<temporaryStorage<<" is zero. Object'll be destroyed" <<endl;	
		if(storedObject!= NULL){
			delete storedObject; //destroy the object
			referenceCounter = 1;
		}
		_getch(); // For checking if all objects deleted
	}
	
}

template <typename TYPE>
SHSmartPtr<TYPE>::SHSmartPtr(const SHSmartPtr &anotherSmartPtr)
{
	storedObject = anotherSmartPtr.storedObject;
	referenceCounter = anotherSmartPtr.referenceCounter;
	++referenceCounter; //Copy constructor must increment reference counter
}

template <typename TYPE>
SHSmartPtr<TYPE>& SHSmartPtr<TYPE>::operator=(const SHSmartPtr &anotherSmartPtr)
{
	if(anotherSmartPtr)
	{
		if(referenceCounter == 1) // If it's the last referens to some object
		{
			SHSmartPtr<TYPE> temporary = *this; //delete this object
			--temporary.referenceCounter; 
		} 
		else //Elese decrement reference counter
		{
			if(referenceCounter)
			{
				--referenceCounter;
			}
		}
		//change the data
		storedObject = anotherSmartPtr.storedObject;
		referenceCounter = anotherSmartPtr.referenceCounter;
		++referenceCounter; //and increment reference counter
	}
	else 
	{
		cout << "Object " << *storedObject << "Will be destroyed" << endl;
		storedObject = NULL;
		referenceCounter = 0;
	}

	return *this;

}
