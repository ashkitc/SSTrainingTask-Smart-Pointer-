#include <iostream>
#include <conio.h>
template <typename TYPE>
class SHSmartPtr
{
public:
	SHSmartPtr() // default constructor
	{
		storedObject = NULL;
		referenceCounter = NULL;
	}
	SHSmartPtr(TYPE *pointerToStore) //Constructor for wrap something in smart poiter
	{
		storedObject = pointerToStore;
		referenceCounter = new int(1); //when new object created it's reference count = 1
	}
	virtual ~SHSmartPtr(); //destructor for clean the memory
	 TYPE* operator -> () { return  storedObject; };
	 TYPE& operator * ()  { return *storedObject; };
	//Copy constructors
	inline SHSmartPtr(const SHSmartPtr &anotherSmartPtr);
	operator bool()const { return storedObject != NULL; }
	//Assignment operator
	SHSmartPtr<TYPE>& operator= (const SHSmartPtr<TYPE>& anotherSmartPtr);
private:
	TYPE *storedObject; //Pointer to object wrapped in smart pointer
    int *referenceCounter; // increments in copy constructor and assignment operator, decrements in destructor
};

template <typename TYPE>
SHSmartPtr<TYPE>::~SHSmartPtr()
{	
	if(storedObject)
	{
		 --( *referenceCounter ); //Decrements referenceCount
		if(*referenceCounter == 0) //And if it equals zero
		{
			cout << "Now reference count in object "<<*storedObject<<" is zero. Object'll be destroyed" <<endl;	
			if(storedObject!= NULL){
				delete storedObject; //destroy the object
				delete referenceCounter;
			}
			_getch(); // For checking if all objects deleted
		}
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
		-- ( *referenceCounter ); //Decrement reference count
		if(*referenceCounter == 0) //If old object hasn't another owner
		{ 
			cout << " Now object " << *storedObject << " will be deleted" << endl;
	        delete storedObject; //delete it
		}
		
		storedObject = anotherSmartPtr.storedObject; //Copy data from another object
	    referenceCounter = anotherSmartPtr.referenceCounter; 
		++ ( *referenceCounter ); //Copy constructor must increment reference counter
	} else 	
	{ 
		storedObject = NULL;  //nullify stored object
		--( *referenceCounter ); //decrement reference count
	}
		return *this;
}
