
#include "driver.h"
#include "list_t.h" //"obj_t.h" is coupled with lists, but can still be used independently
#include <iostream>

LinkedListDriver::LinkedListDriver()
{

}

LinkedListDriver::~LinkedListDriver()
{

}

//quick test for basic functionality || use testType to swap between tests
void LinkedListDriver::RunTest(int dataSize, int testType)
{
	//this variable's type is what will be used as the generic type || brief example of typedef in use: http://stackoverflow.com/questions/457577/catching-access-violation-exceptions
	typedef double DRIVER_TYPE;

	//LinkedList test
	if (testType == 0)
	{
		LinkedList<DRIVER_TYPE> testList;

		//inserting elements
		for (int i = 0; i < dataSize; i++)
		{
			DRIVER_TYPE nObject;
			nObject = i;
			testList.InsertObject(nObject);
		}
		//read values from list
		testList.ResetCursor();
		if (testList.VerifyNextObject())
		{
			for (int i = 0; i < dataSize; i++)
			{
				std::cout << testList.GetNextObject(); //we get an access violation error when test list has no nodes initialized | fixed with bool check!	
			}
		}

		//delete an object
		std::cout << "\nList Length = " << testList.GetLength();
		DRIVER_TYPE testObj;
		testObj = 1;
		testList.DeleteObject(testObj);
		//verify deleted the object
		std::cout << "\nList Length = " << testList.GetLength();
		//clear the list
		testList.EmptyList();
		std::cout << "\nList Length = " << testList.GetLength();
	}
	//ObjLinkedList test
	else if (testType == 1)
	{
		ObjLinkedList<DRIVER_TYPE> testList;
		
		//inserting elements
		for (int i = 0; i < dataSize; i++)
		{
			Obj<DRIVER_TYPE> nObject;
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
		Obj<DRIVER_TYPE> testObj;
		testObj.SetData(1);
		testList.DeleteObject(testObj);
		//verify deleted the object
		std::cout << "\nList Length = " << testList.GetLength();
		//clear the list
		testList.EmptyList();
		std::cout << "\nList Length = " << testList.GetLength();
	}

}

void LinkedListDriver::InitList()
{

}


