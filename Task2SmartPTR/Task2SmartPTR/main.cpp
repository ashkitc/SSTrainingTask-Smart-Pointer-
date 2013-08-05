
#include <iostream>
#include <conio.h>
#include "SHSmartPtr.h"
#include <string>
using namespace std;
void show(SHSmartPtr<string> obj);
int main(int argc, char **argv)
{
	//create two objects wrapped by smart pointers
	SHSmartPtr<string> ptr(new string("first")); 
	cout << *ptr << endl;
	SHSmartPtr<string> ptr2(new string("second"));
	// some block for checking if temporary objects deletes corectly
	if (true)
	{
		SHSmartPtr<string> anohterPtr = ptr; //Creating smart pointer inside the block (using copy constructor)
		cout << *anohterPtr << endl;
		anohterPtr = ptr; //Try assignment operator
		show(anohterPtr); //Pass smart pointer into the function by value, for check if temporarty objects deletes corectly
		SHSmartPtr<string> ptr3(new string("third"));  //creating new smart poiner inside the block
		ptr3 = ptr2; //another test of assignment operator
		ptr3.reset();
		ptr3 = ptr2;
		cout << *ptr3;
	}

	SHSmartPtr<int> myInt;
	SHSmartPtr<int> myInt2(myInt);
	return 0;
}
void show(SHSmartPtr<string> obj)
{
	cout << *obj << endl;
}