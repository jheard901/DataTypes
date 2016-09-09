
#include "driver.h"
#include <iostream>

LinkedListDriver::LinkedListDriver()
{

}

LinkedListDriver::~LinkedListDriver()
{

}

//need to update this since switching to templates for the linkedlist now
void LinkedListDriver::RunTest(int dataSize)
{
	//quick test for basic functionality
	LinkedList testList;

	//inserting elements
	for (int i = 0; i < dataSize; i++)
	{
		Obj nObject;
		nObject.SetIntData(i);
		testList.InsertObject(nObject);
	}
	//read values from list
	testList.ResetCursor();
	for (int i = 0; i < dataSize; i++)
	{
		std::cout << testList.GetNextObject().GetIntData();
	}
	//delete an object
	std::cout << "\nList Length = " << testList.GetLength();
	Obj testObj;
	testObj.SetIntData(1);
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
