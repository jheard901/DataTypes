
#include "driver.h"
#include "list_t.h"
//#include "obj_t.h" //comment this out when turning obj into a template class
#include <iostream>

LinkedListDriver::LinkedListDriver()
{

}

LinkedListDriver::~LinkedListDriver()
{

}

//quick test for basic functionality
void LinkedListDriver::RunTest(int dataSize)
{
	//this variable's type is what will be used as the generic type in LinkedList || brief example of typedef in use: http://stackoverflow.com/questions/457577/catching-access-violation-exceptions
	typedef Obj<double> DRIVER_TYPE;

	//LinkedList<Obj> testList;
	LinkedList<DRIVER_TYPE> testList;

	//inserting elements
	for (int i = 0; i < dataSize; i++)
	{
		//Obj nObject;
		DRIVER_TYPE nObject;
		nObject.SetData(i);
		testList.InsertObject(nObject);
	}
	//read values from list
	testList.ResetCursor();
	if (testList.VerifyNextObject())
	{
		for (int i = 0; i < dataSize; i++)
		{
			std::cout << testList.GetNextObject().GetData(); //we get an access violation error when test list has no nodes initialized | fixed with bool check!	
		}
	}
		
	
	//delete an object
	std::cout << "\nList Length = " << testList.GetLength();
	//Obj testObj;
	DRIVER_TYPE testObj;
	testObj.SetData(1);
	testList.DeleteObject(testObj);
	//verify deleted the object
	std::cout << "\nList Length = " << testList.GetLength();
	//clear the list
	testList.EmptyList();
	std::cout << "\nList Length = " << testList.GetLength();
	

}

void LinkedListDriver::InitList()
{

}


